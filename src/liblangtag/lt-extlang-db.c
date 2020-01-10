/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-extlang-db.c
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

#include <string.h>
#include <libxml/xpath.h>
#include "lt-error.h"
#include "lt-extlang.h"
#include "lt-extlang-private.h"
#include "lt-iter-private.h"
#include "lt-lock.h"
#include "lt-mem.h"
#include "lt-messages.h"
#include "lt-trie.h"
#include "lt-utils.h"
#include "lt-xml.h"
#include "lt-extlang-db.h"


/**
 * SECTION:lt-extlang-db
 * @Short_Description: An interface to access Extlang Database
 * @Title: Database - Extlang
 *
 * This class provides an interface to access Extlang database. which has been
 * registered as ISO 639 code.
 */
struct _lt_extlang_db_t {
	lt_iter_tmpl_t  parent;
	lt_trie_t      *extlang_entries;
};
typedef struct _lt_extlang_db_iter_t {
	lt_iter_t  parent;
	lt_iter_t *iter;
} lt_extlang_db_iter_t;

LT_LOCK_DEFINE_STATIC (edb);

/*< private >*/
static lt_bool_t
lt_extlang_db_parse(lt_extlang_db_t  *extlangdb,
		    lt_error_t      **error)
{
	lt_xml_t *xml;
	lt_bool_t retval = TRUE;
	xmlDocPtr doc = NULL;
	xmlXPathContextPtr xctxt = NULL;
	xmlXPathObjectPtr xobj = NULL;
	lt_error_t *err = NULL;
	int i, n;
	lt_extlang_t *le;

	lt_return_val_if_fail (extlangdb != NULL, FALSE);

	extlangdb->extlang_entries = lt_trie_new();
	lt_mem_add_ref((lt_mem_t *)extlangdb, extlangdb->extlang_entries,
		       (lt_destroy_func_t)lt_trie_unref);
	le = lt_extlang_create();
	lt_extlang_set_tag(le, "*");
	lt_extlang_set_name(le, "Wildcard entry");
	lt_trie_replace(extlangdb->extlang_entries,
			lt_extlang_get_tag(le),
			le,
			(lt_destroy_func_t)lt_extlang_unref);
	le = lt_extlang_create();
	lt_extlang_set_tag(le, "");
	lt_extlang_set_name(le, "Empty entry");
	lt_trie_replace(extlangdb->extlang_entries,
			lt_extlang_get_tag(le),
			le,
			(lt_destroy_func_t)lt_extlang_unref);

	xml = lt_xml_new();
	doc = lt_xml_get_subtag_registry(xml);
	xctxt = xmlXPathNewContext(doc);
	if (!xctxt) {
		lt_error_set(&err, LT_ERR_OOM,
			     "Unable to create an instance of xmlXPathContextPtr.");
		goto bail;
	}
	xobj = xmlXPathEvalExpression((const xmlChar *)"/registry/extlang", xctxt);
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
		xmlChar *subtag = NULL, *desc = NULL, *macrolang = NULL, *preferred = NULL, *prefix = NULL;
		lt_extlang_t *le = NULL;
		char *s;

		if (!ent) {
			lt_error_set(&err, LT_ERR_FAIL_ON_XML,
				     "Unable to obtain the xml node via XPath.");
			goto bail;
		}
		cnode = ent->children;
		while (cnode != NULL) {
			if (xmlStrcmp(cnode->name, (const xmlChar *)"subtag") == 0) {
				if (subtag) {
					lt_warning("Duplicate subtag element in extlang: previous value was '%s'",
						   subtag);
				} else {
					subtag = xmlNodeGetContent(cnode);
				}
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"added") == 0 ||
				   xmlStrcmp(cnode->name, (const xmlChar *)"text") == 0 ||
				   xmlStrcmp(cnode->name, (const xmlChar *)"deprecated") == 0) {
				/* ignore it */
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"description") == 0) {
				/* wonder if many descriptions helps something. or is it a bug? */
				if (!desc)
					desc = xmlNodeGetContent(cnode);
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"macrolanguage") == 0) {
				if (macrolang) {
					lt_warning("Duplicate macrolanguage element in extlang: previous value was '%s'",
						   macrolang);
				} else {
					macrolang = xmlNodeGetContent(cnode);
				}
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"preferred-value") == 0) {
				if (preferred) {
					lt_warning("Duplicate preferred-value element in extlang: previous value was '%s'",
						   preferred);
				} else {
					preferred = xmlNodeGetContent(cnode);
				}
			} else if (xmlStrcmp(cnode->name, (const xmlChar *)"prefix") == 0) {
				if (prefix) {
					lt_warning("Duplicate prefix element in extlang: previous value was '%s'",
						   prefix);
				} else {
					prefix = xmlNodeGetContent(cnode);
				}
			} else {
				lt_warning("Unknown node under /registry/extlang: %s", cnode->name);
			}
			cnode = cnode->next;
		}
		if (!subtag) {
			lt_warning("No subtag node: description = '%s', macrolanguage = '%s', preferred-value = '%s', prefix = '%s'",
				   desc, macrolang, preferred, prefix);
			goto bail1;
		}
		if (!desc) {
			lt_warning("No description node: subtag = '%s', macrolanguage = '%s', preferred-value = '%s', prefix = '%s'",
				   subtag, macrolang, preferred, prefix);
			goto bail1;
		}
		le = lt_extlang_create();
		if (!le) {
			lt_error_set(&err, LT_ERR_OOM,
				     "Unable to create an instance of lt_extlang_t.");
			goto bail1;
		}
		lt_extlang_set_tag(le, (const char *)subtag);
		lt_extlang_set_name(le, (const char *)desc);
		if (macrolang)
			lt_extlang_set_macro_language(le, (const char *)macrolang);
		if (preferred)
			lt_extlang_set_preferred_tag(le, (const char *)preferred);
		if (prefix)
			lt_extlang_add_prefix(le, (const char *)prefix);

		s = strdup(lt_extlang_get_tag(le));
		lt_trie_replace(extlangdb->extlang_entries,
				lt_strlower(s),
				lt_extlang_ref(le),
				(lt_destroy_func_t)lt_extlang_unref);
		free(s);
	  bail1:
		if (subtag)
			xmlFree(subtag);
		if (desc)
			xmlFree(desc);
		if (macrolang)
			xmlFree(macrolang);
		if (preferred)
			xmlFree(preferred);
		if (prefix)
			xmlFree(prefix);
		lt_extlang_unref(le);
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
_lt_extlang_db_iter_init(lt_iter_tmpl_t *tmpl)
{
	lt_extlang_db_iter_t *retval;
	lt_extlang_db_t *extlangdb = (lt_extlang_db_t *)tmpl;

	LT_LOCK (edb);
	if (!extlangdb->extlang_entries) {
		if (!lt_extlang_db_parse(extlangdb, NULL)) {
			LT_UNLOCK (edb);
			return NULL;
		}
	}
	LT_UNLOCK (edb);

	retval = malloc(sizeof (lt_extlang_db_iter_t));
	if (!retval)
		return NULL;
	retval->iter = LT_ITER_INIT (extlangdb->extlang_entries);
	if (!retval->iter) {
		free(retval);
		return NULL;
	}

	return &retval->parent;
}

static void
_lt_extlang_db_iter_fini(lt_iter_t *iter)
{
	lt_extlang_db_iter_t *db_iter = (lt_extlang_db_iter_t *)iter;

	lt_iter_finish(db_iter->iter);
}

static lt_bool_t
_lt_extlang_db_iter_next(lt_iter_t    *iter,
			 lt_pointer_t *key,
			 lt_pointer_t *val)
{
	lt_extlang_db_iter_t *db_iter = (lt_extlang_db_iter_t *)iter;

	return lt_iter_next(db_iter->iter, key, val);
}

/*< public >*/
/**
 * lt_extlang_db_new:
 *
 * Create a new instance of a #lt_extlang_db_t.
 *
 * Returns: (transfer full): a new instance of #lt_extlang_db_t.
 */
lt_extlang_db_t *
lt_extlang_db_new(void)
{
	lt_extlang_db_t *retval = lt_mem_alloc_object(sizeof (lt_extlang_db_t));

	if (retval)
		LT_ITER_TMPL_INIT (&retval->parent, _lt_extlang_db);

	return retval;
}

/**
 * lt_extlang_db_ref:
 * @extlangdb: a #lt_extlang_db_t.
 *
 * Increases the reference count of @extlangdb.
 *
 * Returns: (transfer none): the same @extlangdb object.
 */
lt_extlang_db_t *
lt_extlang_db_ref(lt_extlang_db_t *extlangdb)
{
	lt_return_val_if_fail (extlangdb != NULL, NULL);

	return lt_mem_ref((lt_mem_t *)extlangdb);
}

/**
 * lt_extlang_db_unref:
 * @extlangdb: a #lt_extlang_db_t.
 *
 * Decreases the reference count of @extlangdb. when its reference count
 * drops to 0, the object is finalized (i.e. its memory is freed).
 */
void
lt_extlang_db_unref(lt_extlang_db_t *extlangdb)
{
	if (extlangdb)
		lt_mem_unref((lt_mem_t *)extlangdb);
}

/**
 * lt_extlang_db_lookup:
 * @extlangdb: a #lt_extlang_db_t.
 * @subtag: a subtag name to lookup.
 *
 * Lookup @lt_extlang_t if @subtag is valid and registered into the database.
 *
 * Returns: (transfer full): a #lt_extlang_t that meets with @subtag.
 *                           otherwise %NULL.
 */
lt_extlang_t *
lt_extlang_db_lookup(lt_extlang_db_t *extlangdb,
		     const char      *subtag)
{
	lt_extlang_t *retval;
	char *s;

	lt_return_val_if_fail (extlangdb != NULL, NULL);
	lt_return_val_if_fail (subtag != NULL, NULL);

	LT_LOCK (edb);
	if (!extlangdb->extlang_entries) {
		if (!lt_extlang_db_parse(extlangdb, NULL)) {
			LT_UNLOCK (edb);
			return NULL;
		}
	}
	LT_UNLOCK (edb);

	s = strdup(subtag);
	retval = lt_trie_lookup(extlangdb->extlang_entries,
				lt_strlower(s));
	free(s);
	if (retval)
		return lt_extlang_ref(retval);

	return NULL;
}
