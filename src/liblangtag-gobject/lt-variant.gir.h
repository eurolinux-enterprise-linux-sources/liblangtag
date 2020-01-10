#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-variant.h
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

#ifndef __LT_VARIANT_H__
#define __LT_VARIANT_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-list.gir.h>

LT_BEGIN_DECLS

/**
 * LtVariant:
 *
 * All the fields in the <structname>LtVariant</structname>
 * structure are private to the #LtVariant implementation.
 */
typedef struct _LtVariant	LtVariant;


LtVariant    *lt_variant_ref              (LtVariant       *variant);
void             lt_variant_unref            (LtVariant       *variant);
const char      *lt_variant_get_better_tag   (const LtVariant *variant);
const char      *lt_variant_get_tag          (const LtVariant *variant);
const char      *lt_variant_get_preferred_tag(const LtVariant *variant);
const char      *lt_variant_get_name         (const LtVariant *variant);
const LtList *lt_variant_get_prefix       (const LtVariant *variant);
void             lt_variant_dump             (const LtVariant *variant);
LtBool        lt_variant_compare          (const LtVariant *v1,
                                              const LtVariant *v2);

LT_END_DECLS

#endif /* __LT_VARIANT_H__ */
