/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-variant-db.c
 * Copyright (C) 2011-2016 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <libxml/xpath.h>
#include "lt-error.h"
#include "lt-iter-private.h"
#include "lt-variant.h"
#include "lt-variant-private.h"
#include "lt-list.h"
#include "lt-lock.h"
#include "lt-mem.h"
#include "lt-messages.h"
#include "lt-trie.h"
#include "lt-utils.h"
#include "lt-xml.h"
#include "lt-variant-db.h"


/**
 * SECTION: lt-variant-db
 * @Short_Description: An interface to access Variant Database
 * @Title: Database - Variant
 *
 * This class provides an interface to access Variant database. which has been
 * registered with IANA.
 */
struct _lt_variant_db_t {
	lt_iter_tmpl_t  parent;
	lt_trie_t      *variant_entries;
};
typedef struct _lt_variant_db_iter_t {
	lt_iter_t  parent;
	lt_iter_t *iter;
} lt_variant_db_iter_t;

LT_LOCK_DEFINE_STATIC (vdb);

/*< private >*/
static lt_bool_t
lt_variant_db_parse(lt_variant_db_t  *variantdb,
		    lt_error_t      **error)
{
	lt_xml_t *xml;
	lt_variant_t *le;
	lt_bool_t retval = TRUE;
	xmlDocPtr doc = NULL;
	xmlXPathContextPtr xctxt = NULL;
	xmlXPathObjectPtr xobj = NULL;
	lt_error_t *err = NULL;
	int i, n;

	lt_return_val_if_fail (variantdb != NULL, FALSE);

	variantdb->variant_entries = lt_trie_new();
	lt_mem_add_ref((lt_mem_t *)variantdb, variantdb->variant_entries,
		       (lt_destroy_func_t)lt_trie_unref);
	le = lt_variant_create();
	lt_variant_set_tag(le, "*");
	lt_variant_set_name(le, "Wildcard entry");
	lt_trie_replace(variantdb->variant_entries,
			lt_variant_get_tag(le),
			le,
			(lt_destroy_func_t)lt_variant_unref);
	le = lt_variant_create();
	lt_variant_set_tag(le, "");
	lt_variant_set_name(le, "Empty entry");
	lt_trie_replace(variantdb->variant_entries,
			lt_variant_get_tag(le),
			le,
			(lt_destroy_func_t)lt_variant_unref);

	xml = lt_xml_new();
	doc = lt_xml_get_subtag_registry(xml);
	xctxt = xmlXPathNewContext(doc);
	if (!xctxt) {
		lt_error_set(&err, LT_ERR_OOM,
			     "Unable to create an instance of xmlXPathContextPtr.");
		goto bail;
	}
	xobj = xmlXPathEvalExpression((const xmlChar *)"/registry/variant", xctxt);
	if (!xobj) {
		lt_error_set(&err, LT_ERR_FAIL_ON_XML,
			     "No valid elements for %s",
			     doc->name);
		goto bail;
	}
	n = xmlXPathNodeSetGetLength(xobj->nodesetval);

	for (i = 0; i < n; i++) {
		xmlNodePtr ent = xmlXPathNodeSetItem(xobj->nodesetval, i);
		xmlNodePtr cnode;
		xmlChar *subtag = NULL, *desc = NULL, *preferred = NULL;
		lt_variant_t *le = NULL;
		char *s;
		lt_list_t *prefix_list = NULL, *l;

		if (!ent) {
			lt_error_set(&err, LT_ERR_FAIL_ON_XML,
				     "Unable to obtain the xml node via XPath.");
			goto bail;
		}
		cnode = ent->children;
		while (cnode != NULL) {
			if (xmlStrcmp(cnode->name, (const xmlChar *)"subtag") == 0) {
				if (subtag) {
					lt_warning("Duplicate subtag element in variant: previous value was '%s'",
						   subtag);
				} else {
					subtag = xmlNodeGetContent(cnode);
				}
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"added") == 0 ||
				   xmlStrcmp(cnode->name, (const xmlChar *)"text") == 0 ||
				   xmlStrcmp(cnode->name, (const xmlChar *)"comments") == 0 ||
				   xmlStrcmp(cnode->name, (const xmlChar *)"deprecated") == 0) {
				/* ignore it */
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"description") == 0) {
				/* wonder if many descriptions helps something or is it a bug? */
				if (!desc)
					desc = xmlNodeGetContent(cnode);
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"prefix") == 0) {
				prefix_list = lt_list_append(prefix_list,
							     xmlNodeGetContent(cnode),
							     (lt_destroy_func_t)xmlFree);
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"preferred-value") == 0) {
				if (preferred) {
					lt_warning("Duplicate preferred-value element in variant: previous value was '%s'",
						   preferred);
				} else {
					preferred = xmlNodeGetContent(cnode);
				}
			} else {
				lt_warning("Unknown node under /registry/variant: %s", cnode->name);
			}
			cnode = cnode->next;
		}
		if (!subtag) {
			lt_warning("No subtag node: description = '%s', prefix = '%s', preferred-value = '%s'",
				   desc, prefix_list ? (char *)lt_list_value(prefix_list) : "N/A", preferred);
			goto bail1;
		}
		if (!desc) {
			lt_warning("No description node: subtag = '%s', prefix = '%s', preferred-value = '%s'",
				   subtag, prefix_list ? (char *)lt_list_value(prefix_list) : "N/A", preferred);
			goto bail1;
		}
		le = lt_variant_create();
		if (!le) {
			lt_error_set(&err, LT_ERR_OOM,
				     "Unable to create an instance of lt_variant_t.");
			goto bail1;
		}
		lt_variant_set_tag(le, (const char *)subtag);
		lt_variant_set_name(le, (const char *)desc);
		for (l = prefix_list; l != NULL; l = lt_list_next(l)) {
			lt_variant_add_prefix(le, lt_list_value(l));
		}
		lt_list_free(prefix_list);
		if (preferred)
			lt_variant_set_preferred_tag(le, (const char *)preferred);

		s = strdup(lt_variant_get_tag(le));
		lt_trie_replace(variantdb->variant_entries,
				lt_strlower(s),
				lt_variant_ref(le),
				(lt_destroy_func_t)lt_variant_unref);
		free(s);
	  bail1:
		if (subtag)
			xmlFree(subtag);
		if (desc)
			xmlFree(desc);
		if (preferred)
			xmlFree(preferred);
		lt_variant_unref(le);
	}
  bail:
	if (lt_error_is_set(err, LT_ERR_ANY)) {
		if (error)
			*error = lt_error_ref(err);
		else
			lt_error_print(err, LT_ERR_ANY);
		lt_error_unref(err);
		retval = FALSE;
	}

	if (xobj)
		xmlXPathFreeObject(xobj);
	if (xctxt)
		xmlXPathFreeContext(xctxt);
	if (xml)
		lt_xml_unref(xml);

	return retval;
}

static lt_iter_t *
_lt_variant_db_iter_init(lt_iter_tmpl_t *tmpl)
{
	lt_variant_db_iter_t *retval;
	lt_variant_db_t *db = (lt_variant_db_t *)tmpl;

	LT_LOCK (vdb);
	if (!db->variant_entries) {
		if (!lt_variant_db_parse(db, NULL)) {
			LT_UNLOCK (vdb);
			return NULL;
		}
	}
	LT_UNLOCK (vdb);

	retval = malloc(sizeof (lt_variant_db_iter_t));
	if (!retval)
		return NULL;
	retval->iter = LT_ITER_INIT (db->variant_entries);
	if (!retval->iter) {
		free(retval);
		return NULL;
	}

	return &retval->parent;
}

static void
_lt_variant_db_iter_fini(lt_iter_t *iter)
{
	lt_variant_db_iter_t *db_iter = (lt_variant_db_iter_t *)iter;

	lt_iter_finish(db_iter->iter);
}

static lt_bool_t
_lt_variant_db_iter_next(lt_iter_t    *iter,
			 lt_pointer_t *key,
			 lt_pointer_t *val)
{
	lt_variant_db_iter_t *db_iter = (lt_variant_db_iter_t *)iter;

	return lt_iter_next(db_iter->iter, key, val);
}

/*< public >*/
/**
 * lt_variant_db_new:
 *
 * Create a new instance of a #lt_variant_db_t.
 *
 * Returns: (transfer full): a new instance of #lt_variant_db_t.
 */
lt_variant_db_t *
lt_variant_db_new(void)
{
	lt_variant_db_t *retval = lt_mem_alloc_object(sizeof (lt_variant_db_t));

	if (retval)
		LT_ITER_TMPL_INIT (&retval->parent, _lt_variant_db);

	return retval;
}

/**
 * lt_variant_db_ref:
 * @variantdb: a #lt_variant_db_t.
 *
 * Increases the reference count of @variantdb.
 *
 * Returns: (transfer none): the same @variantdb object.
 */
lt_variant_db_t *
lt_variant_db_ref(lt_variant_db_t *variantdb)
{
	lt_return_val_if_fail (variantdb != NULL, NULL);

	return lt_mem_ref((lt_mem_t *)variantdb);
}

/**
 * lt_variant_db_unref:
 * @variantdb: a #lt_variant_db_t.
 *
 * Decreases the reference count of @variantdb. when its reference count
 * drops to 0, the object is finalized (i.e. its memory is freed).
 */
void
lt_variant_db_unref(lt_variant_db_t *variantdb)
{
	if (variantdb)
		lt_mem_unref((lt_mem_t *)variantdb);
}

/**
 * lt_variant_db_lookup:
 * @variantdb: a #lt_variant_db_t.
 * @subtag: a subtag name to lookup.
 *
 * Lookup @lt_variant_t if @subtag is valid and registered into the database.
 *
 * Returns: (transfer full): a #lt_variant_t that meets with @subtag.
 *                           otherwise %NULL.
 */
lt_variant_t *
lt_variant_db_lookup(lt_variant_db_t *variantdb,
		     const char      *subtag)
{
	lt_variant_t *retval;
	char *s;

	lt_return_val_if_fail (variantdb != NULL, NULL);
	lt_return_val_if_fail (subtag != NULL, NULL);

	LT_LOCK (vdb);
	if (!variantdb->variant_entries) {
		if (!lt_variant_db_parse(variantdb, NULL)) {
			LT_UNLOCK (vdb);
			return NULL;
		}
	}
	LT_UNLOCK (vdb);

	s = strdup(subtag);
	retval = lt_trie_lookup(variantdb->variant_entries,
				lt_strlower(s));
	free(s);
	if (retval)
		return lt_variant_ref(retval);

	return NULL;
}
