#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-extlang.h
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

#ifndef __LT_EXTLANG_H__
#define __LT_EXTLANG_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtExtlang:
 *
 * All the fields in the <structname>LtExtlang</structname>
 * structure are private to the #LtExtlang implementation.
 */
typedef struct _LtExtlang	LtExtlang;


LtExtlang *lt_extlang_ref               (LtExtlang       *extlang);
void          lt_extlang_unref             (LtExtlang       *extlang);
const char   *lt_extlang_get_tag           (const LtExtlang *extlang);
const char   *lt_extlang_get_preferred_tag (const LtExtlang *extlang);
const char   *lt_extlang_get_name          (const LtExtlang *extlang);
const char   *lt_extlang_get_macro_language(const LtExtlang *extlang);
const char   *lt_extlang_get_prefix        (const LtExtlang *extlang);
void          lt_extlang_dump              (const LtExtlang *extlang);
LtBool     lt_extlang_compare           (const LtExtlang *v1,
					    const LtExtlang *v2);

LT_END_DECLS

#endif /* __LT_EXTLANG_H__ */
