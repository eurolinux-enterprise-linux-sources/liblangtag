#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-extension.h
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

#ifndef __LT_EXTENSION_H__
#define __LT_EXTENSION_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtExtension:
 *
 * All the fields in the <structname>LtExtension</structname>
 * structure are private to the #LtExtension implementation.
 */
typedef struct _LtExtension		LtExtension;


LtExtension *lt_extension_ref                  (LtExtension       *extension);
void            lt_extension_unref                (LtExtension       *extension);
const char     *lt_extension_get_tag              (LtExtension       *extension);
char           *lt_extension_get_canonicalized_tag(LtExtension       *extension);
void            lt_extension_dump                 (LtExtension       *extension);
LtBool       lt_extension_compare              (const LtExtension *v1,
                                                   const LtExtension *v2);
LtBool       lt_extension_truncate             (LtExtension       *extension);

LT_END_DECLS

#endif /* __LT_EXTENSION_H__ */
