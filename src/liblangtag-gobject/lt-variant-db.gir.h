#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-variant-db.h
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

#ifndef __LT_VARIANT_DB_H__
#define __LT_VARIANT_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-variant.gir.h>

LT_BEGIN_DECLS

/**
 * LtVariantDb:
 *
 * All the fields in the <structname>LtVariantDb</structname>
 * structure are private to the #LtVariantDb implementation.
 */
typedef struct _LtVariantDb	LtVariantDb;


LtVariantDb *lt_variant_db_new   (void);
LtVariantDb *lt_variant_db_ref   (LtVariantDb *variantdb);
void             lt_variant_db_unref (LtVariantDb *variantdb);
LtVariant    *lt_variant_db_lookup(LtVariantDb *variantdb,
                                      const char      *subtag);

LT_END_DECLS

#endif /* __LT_VARIANT_DB_H__ */
