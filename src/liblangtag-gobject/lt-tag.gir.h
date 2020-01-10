#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-tag.h
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

#ifndef __LT_TAG_H__
#define __LT_TAG_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-list.gir.h>
#include <liblangtag-gobject/lt-string.gir.h>
#include <liblangtag-gobject/lt-lang.gir.h>
#include <liblangtag-gobject/lt-extlang.gir.h>
#include <liblangtag-gobject/lt-script.gir.h>
#include <liblangtag-gobject/lt-region.gir.h>
#include <liblangtag-gobject/lt-extension.gir.h>
#include <liblangtag-gobject/lt-grandfathered.gir.h>

LT_BEGIN_DECLS

/**
 * LtTag:
 *
 * All the fields in the <structname>LtTag</structname>
 * structure are private to the #LtTag implementation.
 */
typedef struct _LtTag	LtTag;


LtTag                 *lt_tag_new                       (void);
LtTag                 *lt_tag_ref                       (LtTag        *tag);
void                      lt_tag_unref                     (LtTag        *tag);
LtBool                 lt_tag_parse                     (LtTag        *tag,
                                                            const char      *tag_string,
                                                            LtError     **error);
LtBool                 lt_tag_parse_with_extra_token    (LtTag        *tag,
                                                            const char      *tag_string,
                                                            LtError     **error);
void                      lt_tag_clear                     (LtTag        *tag);
LtTag                 *lt_tag_copy                      (const LtTag  *tag);
LtBool                 lt_tag_truncate                  (LtTag        *tag,
                                                            LtError     **error);
const char               *lt_tag_get_string                (LtTag        *tag);
char                     *lt_tag_canonicalize              (LtTag        *tag,
                                                            LtError     **error);
char                     *lt_tag_convert_to_locale         (LtTag        *tag,
                                                            LtError     **error);
LtTag                 *lt_tag_convert_from_locale       (LtError     **error);
LtTag                 *lt_tag_convert_from_locale_string(const char      *locale,
                                                            LtError     **error);
void                      lt_tag_dump                      (const LtTag  *tag);
LtBool                 lt_tag_compare                   (const LtTag  *v1,
                                                            const LtTag  *v2);
LtBool                 lt_tag_match                     (const LtTag  *v1,
                                                            const char      *v2,
                                                            LtError     **error);
char                     *lt_tag_lookup                    (const LtTag  *tag,
                                                            const char      *pattern,
                                                            LtError     **error);
char                     *lt_tag_transform                 (LtTag        *tag,
                                                            LtError     **error);
const LtLang          *lt_tag_get_language              (const LtTag  *tag);
const LtExtlang       *lt_tag_get_extlang               (const LtTag  *tag);
const LtScript        *lt_tag_get_script                (const LtTag  *tag);
const LtRegion        *lt_tag_get_region                (const LtTag  *tag);
const LtList          *lt_tag_get_variants              (const LtTag  *tag);
const LtExtension     *lt_tag_get_extension             (const LtTag  *tag);
const LtString        *lt_tag_get_privateuse            (const LtTag  *tag);
const LtGrandfathered *lt_tag_get_grandfathered         (const LtTag  *tag);

LT_END_DECLS

#endif /* __LT_TAG_H__ */
