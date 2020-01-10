#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-lang.h
 * Copyright (C) 2011-2012 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#if !defined (__LANGTAG_H__INSIDE) && !defined (__LANGTAG_COMPILATION)
#error "Only <liblangtag/langtag.h> can be included directly."
#endif

#ifndef __LT_LANG_H__
#define __LT_LANG_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtLang:
 *
 * All the fields in the <structname>LtLang</structname>
 * structure are private to the #LtLang implementation.
 */
typedef struct _LtLang	LtLang;


LtLang  *lt_lang_ref                (LtLang       *lang);
void        lt_lang_unref              (LtLang       *lang);
const char *lt_lang_get_name           (const LtLang *lang);
const char *lt_lang_get_better_tag     (const LtLang *lang);
const char *lt_lang_get_tag            (const LtLang *lang);
const char *lt_lang_get_preferred_tag  (const LtLang *lang);
const char *lt_lang_get_suppress_script(const LtLang *lang);
const char *lt_lang_get_macro_language (const LtLang *lang);
const char *lt_lang_get_scope          (const LtLang *lang);
void        lt_lang_dump               (const LtLang *lang);
LtBool   lt_lang_compare            (const LtLang *v1,
					const LtLang *v2);

LT_END_DECLS

#endif /* __LT_LANG_H__ */
