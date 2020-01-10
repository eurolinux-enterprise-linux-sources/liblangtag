#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-redundant-db.h
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

#ifndef __LT_REDUNDANT_DB_H__
#define __LT_REDUNDANT_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-redundant.gir.h>

LT_BEGIN_DECLS

/**
 * LtRedundantDb:
 *
 * All the fields in the <structname>LtRedundantDb</structname>
 * structure are private to the #LtRedundantDb implementation.
 */
typedef struct _LtRedundantDb	LtRedundantDb;


LtRedundantDb *lt_redundant_db_new   (void);
LtRedundantDb *lt_redundant_db_ref   (LtRedundantDb *redundantdb);
void               lt_redundant_db_unref (LtRedundantDb *redundantdb);
LtRedundant    *lt_redundant_db_lookup(LtRedundantDb *redundantdb,
                                          const char        *tag);

LT_END_DECLS

#endif /* __LT_REDUNDANT_DB_H__ */
