#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-database.h
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

#ifndef __LT_DATABASE_H__
#define __LT_DATABASE_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-extlang-db.gir.h>
#include <liblangtag-gobject/lt-grandfathered-db.gir.h>
#include <liblangtag-gobject/lt-lang-db.gir.h>
#include <liblangtag-gobject/lt-redundant-db.gir.h>
#include <liblangtag-gobject/lt-region-db.gir.h>
#include <liblangtag-gobject/lt-script-db.gir.h>
#include <liblangtag-gobject/lt-variant-db.gir.h>

LT_BEGIN_DECLS

void                   lt_db_set_datadir      (const char *path);
const char            *lt_db_get_datadir      (void);
void                   lt_db_initialize       (void);
void                   lt_db_finalize         (void);
LtLangDb          *lt_db_get_lang         (void);
LtExtlangDb       *lt_db_get_extlang      (void);
LtScriptDb        *lt_db_get_script       (void);
LtRegionDb        *lt_db_get_region       (void);
LtVariantDb       *lt_db_get_variant      (void);
LtGrandfatheredDb *lt_db_get_grandfathered(void);
LtRedundantDb     *lt_db_get_redundant    (void);

LT_END_DECLS

#endif /* __LT_DATABASE_H__ */
