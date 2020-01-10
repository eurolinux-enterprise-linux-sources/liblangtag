/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-lang.c
 * Copyright (C) 2011-2012 Akira TAGOH
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
#include "lt-mem.h"
#include "lt-messages.h"
#include "lt-string.h"
#include "lt-utils.h"
#include "lt-lang.h"
#include "lt-lang-private.h"


/**
 * SECTION: lt-lang
 * @Short_Description: A container class for Language subtag
 * @Title: Container - Language
 *
 * This container class provides a data access to Language subtag entry.
 */
struct _lt_lang_t {
	lt_mem_t  parent;
	char     *tag;
	char     *description;
	char     *suppress_script;
	char     *scope;
	char     *macrolanguage;
	char     *preferred_tag;
};

/*< private >*/

/*< protected >*/
lt_lang_t *
lt_lang_create(void)
{
	lt_lang_t *retval = lt_mem_alloc_object(sizeof (lt_lang_t));

	return retval;
}

void
lt_lang_set_name(lt_lang_t  *lang,
		 const char *description)
{
	lt_return_if_fail (lang != NULL);
	lt_return_if_fail (description != NULL);

	if (lang->description)
		lt_mem_delete_ref(&lang->parent, lang->description);
	lang->description = strdup(description);
	lt_mem_add_ref(&lang->parent, lang->description, free);
}

void
lt_lang_set_tag(lt_lang_t  *lang,
		const char *subtag)
{
	lt_return_if_fail (lang != NULL);
	lt_return_if_fail (subtag != NULL);

	if (lang->tag)
		lt_mem_delete_ref(&lang->parent, lang->tag);
	lang->tag = strdup(subtag);
	lt_mem_add_ref(&lang->parent, lang->tag, free);
}

void
lt_lang_set_preferred_tag(lt_lang_t  *lang,
			  const char *subtag)
{
	lt_return_if_fail (lang != NULL);
	lt_return_if_fail (subtag != NULL);

	if (lang->preferred_tag)
		lt_mem_delete_ref(&lang->parent, lang->preferred_tag);
	lang->preferred_tag = strdup(subtag);
	lt_mem_add_ref(&lang->parent, lang->preferred_tag, free);
}

void
lt_lang_set_suppress_script(lt_lang_t  *lang,
			    const char *script)
{
	lt_return_if_fail (lang != NULL);
	lt_return_if_fail (script != NULL);

	if (lang->suppress_script)
		lt_mem_delete_ref(&lang->parent, lang->suppress_script);
	lang->suppress_script = strdup(script);
	lt_mem_add_ref(&lang->parent, lang->suppress_script, free);
}

void
lt_lang_set_macro_language(lt_lang_t  *lang,
			   const char *macrolanguage)
{
	lt_return_if_fail (lang != NULL);
	lt_return_if_fail (macrolanguage != NULL);

	if (lang->macrolanguage)
		lt_mem_delete_ref(&lang->parent, lang->macrolanguage);
	lang->macrolanguage = strdup(macrolanguage);
	lt_mem_add_ref(&lang->parent, lang->macrolanguage, free);
}

void
lt_lang_set_scope(lt_lang_t  *lang,
		  const char *scope)
{
	lt_return_if_fail (lang != NULL);
	lt_return_if_fail (scope != NULL);

	if (lang->scope)
		lt_mem_delete_ref(&lang->parent, lang->scope);
	lang->scope = strdup(scope);
	lt_mem_add_ref(&lang->parent, lang->scope, free);
}

/*< public >*/
/**
 * lt_lang_ref:
 * @lang: a #lt_lang_t.
 *
 * Increases the reference count of @lang.
 *
 * Returns: (transfer none): the same @lang object.
 */
lt_lang_t *
lt_lang_ref(lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lt_mem_ref(&lang->parent);
}

/**
 * lt_lang_unref:
 * @lang: a #lt_lang_t.
 *
 * Decreases the reference count of @lang. when its reference count
 * drops to 0, the object is finalized (i.e. its memory is freed).
 */
void
lt_lang_unref(lt_lang_t *lang)
{
	if (lang)
		lt_mem_unref(&lang->parent);
}

/**
 * lt_lang_get_name:
 * @lang: a #lt_lang_t.
 *
 * Obtains the description of the subtag.
 *
 * Returns: a description string.
 */
const char *
lt_lang_get_name(const lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lang->description;
}

/**
 * lt_lang_get_better_tag:
 * @lang: a #lt_lang_t.
 *
 * Obtains the better tag for use. this is a convenient function to get
 * the preferred-value if available.
 *
 * Returns: a tag string.
 */
const char *
lt_lang_get_better_tag(const lt_lang_t *lang)
{
	const char *retval = lt_lang_get_preferred_tag(lang);

	if (!retval)
		retval = lt_lang_get_tag(lang);

	return retval;
}

/**
 * lt_lang_get_tag:
 * @lang: a #lt_lang_t.
 *
 * Obtains the tag name.
 *
 * Returns: a tag string.
 */
const char *
lt_lang_get_tag(const lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lang->tag;
}

/**
 * lt_lang_get_preferred_tag:
 * @lang: a #lt_lang_t.
 *
 * Obtains the preferred-value. this is available only when the tag is
 * marked as deprecated.
 *
 * Returns: a preferred-value for the tag or %NULL.
 */
const char *
lt_lang_get_preferred_tag(const lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lang->preferred_tag;
}

/**
 * lt_lang_get_suppress_script:
 * @lang: a #lt_lang_t.
 *
 * Obtains the suppress-script value. which shouldn't be used to form
 * language tags with the associated primary or extended language subtag.
 *
 * Returns: a suppress-script string or %NULL.
 */
const char *
lt_lang_get_suppress_script(const lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lang->suppress_script;
}

/**
 * lt_lang_get_macro_language:
 * @lang: a #lt_lang_t.
 *
 * Obtains the macrolanguage being assigned for the subtag.
 * This is available only when the subtag is registered as the macrolanguage
 * in ISO 639-3.
 *
 * Returns: a macrolanguage string or %NULL.
 */
const char *
lt_lang_get_macro_language(const lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lang->macrolanguage;
}

/**
 * lt_lang_get_scope:
 * @lang: a #lt_lang_t.
 *
 * Obtains the scope value indicating the type of language code according
 * to ISO 639.
 *
 * Returns: a scope string or %NULL.
 */
const char *
lt_lang_get_scope(const lt_lang_t *lang)
{
	lt_return_val_if_fail (lang != NULL, NULL);

	return lang->scope;
}

/**
 * lt_lang_dump:
 * @lang: a #lt_lang_t.
 *
 * Dumps the container information to the standard output.
 */
void
lt_lang_dump(const lt_lang_t *lang)
{
	const char *preferred = lt_lang_get_preferred_tag(lang);
	const char *suppress = lt_lang_get_suppress_script(lang);
	const char *scope = lt_lang_get_scope(lang);
	const char *macrolang = lt_lang_get_macro_language(lang);
	lt_string_t *string = lt_string_new(NULL);

	if (preferred) {
		if (lt_string_length(string) == 0)
			lt_string_append(string, " (");
		lt_string_append_printf(string, "preferred-value: %s",
					preferred);
	}
	if (suppress) {
		if (lt_string_length(string) == 0)
			lt_string_append(string, " (");
		else
			lt_string_append(string, ", ");
		lt_string_append_printf(string, "suppress-script: %s",
					suppress);
	}
	if (scope) {
		if (lt_string_length(string) == 0)
			lt_string_append(string, " (");
		else
			lt_string_append(string, ", ");
		lt_string_append_printf(string, "scope: %s",
					scope);
	}
	if (macrolang) {
		if (lt_string_length(string) == 0)
			lt_string_append(string, " (");
		else
			lt_string_append(string, ", ");
		lt_string_append_printf(string, "macrolanguage: %s",
					macrolang);
	}
	if (lt_string_length(string) > 0)
		lt_string_append(string, ")");

	lt_info("Language: %s [%s]%s",
		lt_lang_get_tag(lang),
		lt_lang_get_name(lang),
		lt_string_value(string));

	lt_string_unref(string);
}

/**
 * lt_lang_compare:
 * @v1: a #lt_lang_t.
 * @v2: a #lt_lang_t.
 *
 * Compare if @v1 and @v2 is the same object or not.
 *
 * Returns: %TRUE if it's the same, otherwise %FALSE.
 */
lt_bool_t
lt_lang_compare(const lt_lang_t *v1,
		const lt_lang_t *v2)
{
	const char *s1, *s2;

	if (v1 == v2)
		return TRUE;

	s1 = v1 ? lt_lang_get_tag(v1) : NULL;
	s2 = v2 ? lt_lang_get_tag(v2) : NULL;

	if (lt_strcmp0(s1, "*") == 0 ||
	    lt_strcmp0(s2, "*") == 0)
		return TRUE;

	return lt_strcmp0(s1, s2) == 0;
}
