#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-script.h
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

#ifndef __LT_SCRIPT_H__
#define __LT_SCRIPT_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtScript:
 *
 * All the fields in the <structname>LtScript</structname>
 * structure are private to the #LtScript implementation.
 */
typedef struct _LtScript	LtScript;


LtScript *lt_script_ref                (LtScript       *script);
void         lt_script_unref              (LtScript       *script);
const char  *lt_script_get_name           (const LtScript *script);
const char  *lt_script_get_tag            (const LtScript *script);
void         lt_script_dump               (const LtScript *script);
const char  *lt_script_convert_to_modifier(const LtScript *script);
LtBool    lt_script_compare            (const LtScript *v1,
					   const LtScript *v2);

LT_END_DECLS

#endif /* __LT_SCRIPT_H__ */
