#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-redundant.h
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

#ifndef __LT_REDUNDANT_H__
#define __LT_REDUNDANT_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtRedundant:
 *
 * All the fields in the <structname>LtRedundant</structname>
 * structure are private to the #LtRedundant implementation.
 */
typedef struct _LtRedundant	LtRedundant;


LtRedundant *lt_redundant_ref              (LtRedundant       *redundant);
void            lt_redundant_unref            (LtRedundant       *redundant);
const char     *lt_redundant_get_better_tag   (const LtRedundant *redundant);
const char     *lt_redundant_get_tag          (const LtRedundant *redundant);
const char     *lt_redundant_get_preferred_tag(const LtRedundant *redundant);
const char     *lt_redundant_get_name         (const LtRedundant *redundant);
void            lt_redundant_dump             (const LtRedundant *redundant);
LtBool       lt_redundant_compare          (const LtRedundant *v1,
                                               const LtRedundant *v2);

LT_END_DECLS

#endif /* __LT_REDUNDANT_H__ */
