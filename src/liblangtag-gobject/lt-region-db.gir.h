#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-region-db.h
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

#ifndef __LT_REGION_DB_H__
#define __LT_REGION_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-region.gir.h>

LT_BEGIN_DECLS

/**
 * LtRegionDb:
 *
 * All the fields in the <structname>LtRegionDb</structname>
 * structure are private to the #LtRegionDb implementation.
 */
typedef struct _LtRegionDb		LtRegionDb;


LtRegionDb *lt_region_db_new   (void);
LtRegionDb *lt_region_db_ref   (LtRegionDb *regiondb);
void            lt_region_db_unref (LtRegionDb *regiondb);
LtRegion    *lt_region_db_lookup(LtRegionDb *regiondb,
                                    const char     *language_or_code);

LT_END_DECLS

#endif /* __LT_REGION_DB_H__ */
