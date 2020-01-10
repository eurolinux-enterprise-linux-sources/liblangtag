/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-xml.c
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

#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "lt-error.h"
#include "lt-lock.h"
#include "lt-mem.h"
#include "lt-messages.h"
#include "lt-database.h"
#include "lt-string.h"
#include "lt-utils.h"
#include "lt-xml.h"


struct _lt_xml_t {
	lt_mem_t  parent;
	xmlDocPtr subtag_registry;
	xmlDocPtr cldr_bcp47_calendar;
	xmlDocPtr cldr_bcp47_collation;
	xmlDocPtr cldr_bcp47_currency;
	xmlDocPtr cldr_bcp47_number;
	xmlDocPtr cldr_bcp47_timezone;
	xmlDocPtr cldr_bcp47_transform;
	xmlDocPtr cldr_bcp47_variant;
	xmlDocPtr cldr_supplemental_likelysubtags;
	xmlDocPtr cldr_supplemental_supplementaldata;
	xmlDocPtr cldr_supplemental_supplementalmetadata;
};

static lt_xml_t *__xml = NULL;
LT_LOCK_DEFINE_STATIC (xml);

/*< private >*/
static lt_bool_t
lt_xml_read_subtag_registry(lt_xml_t  *xml,
			    lt_error_t   **error)
{
	lt_string_t *regfile;
	xmlParserCtxtPtr xmlparser = NULL;
	xmlDocPtr doc = NULL;
	lt_error_t *err = NULL;

	lt_return_val_if_fail (xml != NULL, FALSE);

	regfile = lt_string_new(NULL);
#ifdef ENABLE_DEBUG
	LT_STMT_START {
		struct stat st;

		lt_string_append_filename(regfile,
					  BUILDDIR,
					  "data", "language-subtag-registry.xml", NULL);
		if (stat(lt_string_value(regfile), &st) == -1) {
			lt_string_clear(regfile);
#endif
	lt_string_append_filename(regfile,
				  lt_db_get_datadir(),
				  "language-subtag-registry.xml", NULL);
#ifdef ENABLE_DEBUG
		}
	} LT_STMT_END;
#endif
	xmlparser = xmlNewParserCtxt();
	if (!xmlparser) {
		lt_error_set(&err, LT_ERR_OOM,
			     "Unable to create an instance of xmlParserCtxt.");
		goto bail;
	}
	doc = xmlCtxtReadFile(xmlparser, lt_string_value(regfile), "UTF-8", 0);
	if (!doc) {
		lt_error_set(&err, LT_ERR_FAIL_ON_XML,
			     "Unable to read the xml file: %s",
			     lt_string_value(regfile));
		goto bail;
	}
	xml->subtag_registry = doc;
	lt_mem_add_ref(&xml->parent, xml->subtag_registry,
		       (lt_destroy_func_t)xmlFreeDoc);

  bail:
	lt_string_unref(regfile);
	if (xmlparser)
		xmlFreeParserCtxt(xmlparser);

	if (lt_error_is_set(err, LT_ERR_ANY)) {
		if (error)
			*error = lt_error_ref(err);
		else
			lt_error_print(err, LT_ERR_ANY);
		lt_error_unref(err);

		return FALSE;
	}

	return TRUE;
}

static lt_bool_t
lt_xml_read_cldr_bcp47(lt_xml_t     *xml,
		       const char   *filename,
		       xmlDocPtr    *doc,
		       lt_error_t  **error)
{
	lt_string_t *regfile;
	xmlParserCtxtPtr xmlparser = NULL;
	lt_error_t *err = NULL;

	lt_return_val_if_fail (xml != NULL, FALSE);

	regfile = lt_string_new(NULL);
#ifdef ENABLE_DEBUG
	LT_STMT_START {
		struct stat st;

		lt_string_append_filename(regfile,
					  BUILDDIR, "data", "common", "bcp47",
					  filename, NULL);
		if (stat(lt_string_value(regfile), &st) == -1) {
			lt_string_clear(regfile);
			lt_string_append_filename(regfile,
						  SRCDIR, "data", "common", "bcp47",
						  filename, NULL);
			if (stat(lt_string_value(regfile), &st) == -1) {
				lt_string_clear(regfile);
#endif
	lt_string_append_filename(regfile,
				  lt_db_get_datadir(),
				  "common", "bcp47", filename, NULL);
#ifdef ENABLE_DEBUG
			}
		}
	} LT_STMT_END;
#endif
	xmlparser = xmlNewParserCtxt();
	if (!xmlparser) {
		lt_error_set(&err, LT_ERR_OOM,
			     "Unable to create an instance of xmlParserCtxt.");
		goto bail;
	}
	*doc = xmlCtxtReadFile(xmlparser, lt_string_value(regfile), "UTF-8", 0);
	if (!*doc) {
		lt_error_set(&err, LT_ERR_FAIL_ON_XML,
			     "Unable to read the xml file: %s",
			     lt_string_value(regfile));
		goto bail;
	}
	lt_mem_add_ref(&xml->parent, *doc,
		       (lt_destroy_func_t)xmlFreeDoc);

  bail:
	lt_string_unref(regfile);
	if (xmlparser)
		xmlFreeParserCtxt(xmlparser);

	if (lt_error_is_set(err, LT_ERR_ANY)) {
		if (error)
			*error = lt_error_ref(err);
		else
			lt_error_print(err, LT_ERR_ANY);
		lt_error_unref(err);

		return FALSE;
	}

	return TRUE;
}

static lt_bool_t
lt_xml_read_cldr_supplemental(lt_xml_t     *xml,
			      const char   *filename,
			      xmlDocPtr    *doc,
			      lt_error_t  **error)
{
	lt_string_t *regfile = NULL;
	xmlParserCtxtPtr xmlparser = NULL;
	lt_error_t *err = NULL;

	lt_return_val_if_fail (xml != NULL, FALSE);

	regfile = lt_string_new(NULL);
#ifdef ENABLE_DEBUG
	LT_STMT_START {
		struct stat st;

		lt_string_append_filename(regfile,
					  BUILDDIR, "data", "common", "supplemental",
					  filename, NULL);
		lt_info("%s", lt_string_value(regfile));
		if (stat(lt_string_value(regfile), &st) == -1) {
			lt_string_clear(regfile);
			lt_string_append_filename(regfile,
						  SRCDIR, "data", "common", "supplemental",
						  filename, NULL);
			if (stat(lt_string_value(regfile), &st) == -1) {
				lt_string_clear(regfile);
#endif
	lt_string_append_filename(regfile,
				  lt_db_get_datadir(),
				  "common", "supplemental", filename, NULL);
#ifdef ENABLE_DEBUG
			}
		}
	} LT_STMT_END;
#endif
	xmlparser = xmlNewParserCtxt();
	if (!xmlparser) {
		lt_error_set(&err, LT_ERR_OOM,
			     "Unable to create an instance of xmlParserCtxt.");
		goto bail;
	}
	*doc = xmlCtxtReadFile(xmlparser, lt_string_value(regfile), "UTF-8", 0);
	if (!*doc) {
		lt_error_set(&err, LT_ERR_FAIL_ON_XML,
			     "Unable to read the xml file: %s",
			     lt_string_value(regfile));
		goto bail;
	}
	lt_mem_add_ref(&xml->parent, *doc,
		       (lt_destroy_func_t)xmlFreeDoc);

  bail:
	lt_string_unref(regfile);
	if (xmlparser)
		xmlFreeParserCtxt(xmlparser);

	if (lt_error_is_set(err, LT_ERR_ANY)) {
		if (error)
			*error = lt_error_ref(err);
		else
			lt_error_print(err, LT_ERR_ANY);
		lt_error_unref(err);

		return FALSE;
	}

	return TRUE;
}

static lt_bool_t
_lt_xml_merge_keys(lt_xml_t    *xml,
		   xmlDocPtr    doc1,
		   xmlDocPtr    doc2,
		   lt_error_t **error)
{
	xmlXPathContextPtr xctxt = NULL;
	xmlXPathObjectPtr xobj = NULL;
	xmlNodePtr parent_node;
	int i, n;
	lt_bool_t retval = FALSE;

	xctxt = xmlXPathNewContext(doc1);
	if (!xctxt) {
		lt_error_set(error, LT_ERR_OOM,
			     "Unable to create an instance of xmlXPathContextPtr");
		goto bail;
	}
	xobj = xmlXPathEvalExpression((const xmlChar *)"/ldmlBCP47/keyword", xctxt);
	if (!xobj) {
		lt_error_set(error, LT_ERR_FAIL_ON_XML,
			     "No valid elements for %s: keyword",
			     doc1->name);
		goto bail;
	}
	if ((n = xmlXPathNodeSetGetLength(xobj->nodesetval)) != 1) {
		lt_error_set(error, LT_ERR_FAIL_ON_XML,
			     "Too many keyword elements in %s: %s", doc1->name, doc2->name);
		goto bail;
	}
	parent_node = xmlXPathNodeSetItem(xobj->nodesetval, 0);
	xmlXPathFreeObject(xobj);
	xmlXPathFreeContext(xctxt);
	xobj = NULL;
	xctxt = NULL;

	xctxt = xmlXPathNewContext(doc2);
	if (!xctxt) {
		lt_error_set(error, LT_ERR_OOM,
			     "Unable to create an instance of xmlXPathContextPtr");
		goto bail;
	}
	xobj = xmlXPathEvalExpression((const xmlChar *)"/ldmlBCP47/keyword/key", xctxt);
	if (!xobj) {
		lt_error_set(error, LT_ERR_FAIL_ON_XML,
			     "No valid elements for %s: key",
			     doc2->name);
		goto bail;
	}
	n = xmlXPathNodeSetGetLength(xobj->nodesetval);
	for (i = 0; i < n; i++) {
		xmlNodePtr p = xmlDocCopyNode(xmlXPathNodeSetItem(xobj->nodesetval, i), doc1, 1);

		xmlAddChild(parent_node, p);
	}

	retval = TRUE;
  bail:
	if (xobj)
		xmlXPathFreeObject(xobj);
	if (xctxt)
		xmlXPathFreeContext(xctxt);
	lt_mem_remove_ref(&xml->parent, doc2);
	xmlFreeDoc(doc2);

	return retval;
}

/*< public >*/
lt_xml_t *
lt_xml_new(void)
{
	if (__xml)
		return lt_xml_ref(__xml);

	__xml = lt_mem_alloc_object(sizeof (lt_xml_t));
	if (__xml)
		lt_mem_add_weak_pointer(&__xml->parent, (lt_pointer_t *)&__xml);

	return __xml;
}

lt_xml_t *
lt_xml_ref(lt_xml_t *xml)
{
	lt_return_val_if_fail (xml != NULL, NULL);

	return lt_mem_ref(&xml->parent);
}

void
lt_xml_unref(lt_xml_t *xml)
{
	if (xml)
		lt_mem_unref(&xml->parent);
}

xmlDocPtr
lt_xml_get_subtag_registry(lt_xml_t *xml)
{
	lt_error_t *err = NULL;

	lt_return_val_if_fail (xml != NULL, NULL);

	LT_LOCK (xml);
	if (!xml->subtag_registry) {
		if (!lt_xml_read_subtag_registry(xml, &err)) {
			LT_UNLOCK (xml);
			lt_error_print(err, LT_ERR_ANY);
			lt_error_unref(err);
			return NULL;
		}
	}
	LT_UNLOCK (xml);

	return xml->subtag_registry;
}

xmlDocPtr
lt_xml_get_cldr(lt_xml_t      *xml,
		lt_xml_cldr_t  type)
{
	lt_error_t *err = NULL;
	lt_bool_t ret = FALSE;
	xmlDocPtr *pref;
	int idx;
	const char *xml_files[] = {
		"calendar.xml", "collation.xml", "currency.xml", "number.xml", "timezone.xml", "transform.xml:transform_ime.xml:transform_keyboard.xml:transform_mt.xml:transform_private_use.xml", "variant.xml",
		"likelySubtags.xml", "supplementalData.xml", "supplementalMetadata.xml",
		NULL
	};

	LT_ASSERT_STATIC ((sizeof (lt_xml_t) - offsetof (lt_xml_t, cldr_bcp47_calendar)) == (sizeof (lt_pointer_t) * ((LT_XML_CLDR_BCP47_END - LT_XML_CLDR_BCP47_BEGIN + 1) + (LT_XML_CLDR_SUPPLEMENTAL_END - LT_XML_CLDR_SUPPLEMENTAL_BEGIN + 1))));

	lt_return_val_if_fail (xml != NULL, NULL);
	lt_return_val_if_fail (type > LT_XML_CLDR_BEGIN && type < LT_XML_CLDR_END, NULL);

	LT_LOCK (xml);
	pref = &xml->cldr_bcp47_calendar;
	if (type >= LT_XML_CLDR_DUMMY1)
		idx = type - LT_XML_CLDR_DUMMY1 + LT_XML_CLDR_BCP47_END;
	else
		idx = type;

	if (!pref[idx - 1]) {
		if (type >= LT_XML_CLDR_DUMMY1) {
			ret = lt_xml_read_cldr_supplemental(xml, xml_files[idx - 1], &pref[idx - 1], &err);
		} else if (type == LT_XML_CLDR_BCP47_TRANSFORM) {
			const char *pp = xml_files[idx - 1];
			char *p, *s;
			xmlDocPtr *d = &pref[idx - 1], doc = NULL;

			do {
				p = strchr(pp, ':');
				if (p)
					s = lt_strndup(pp, p - pp);
				else
					s = strdup(pp);
				if (!lt_xml_read_cldr_bcp47(xml, s, d, &err))
					goto bail;
				if (d == &doc) {
					if (!_lt_xml_merge_keys(xml, pref[idx - 1], doc, &err))
						goto bail;
				} else {
					d = &doc;
				}
				free(s);
				if (p)
					pp = ++p;
			} while (p);
			ret = TRUE;
		} else {
			ret = lt_xml_read_cldr_bcp47(xml, xml_files[idx - 1], &pref[idx - 1], &err);
		}
	  bail:
		if (!ret) {
			LT_UNLOCK (xml);
			lt_error_print(err, LT_ERR_ANY);
			lt_error_unref(err);
			return NULL;
		}
	}
	LT_UNLOCK (xml);

	return pref[idx - 1];
}
