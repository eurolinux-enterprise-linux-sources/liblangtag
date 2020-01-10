#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-grandfathered-db.h
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

#ifndef __LT_GRANDFATHERED_DB_H__
#define __LT_GRANDFATHERED_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-grandfathered.gir.h>

LT_BEGIN_DECLS

/**
 * LtGrandfatheredDb:
 *
 * All the fields in the <structname>LtGrandfatheredDb</structname>
 * structure are private to the #LtGrandfatheredDb implementation.
 */
typedef struct _LtGrandfatheredDb	LtGrandfatheredDb;


LtGrandfatheredDb *lt_grandfathered_db_new   (void);
LtGrandfatheredDb *lt_grandfathered_db_ref   (LtGrandfatheredDb *grandfathereddb);
void                   lt_grandfathered_db_unref (LtGrandfatheredDb *grandfathereddb);
LtGrandfathered    *lt_grandfathered_db_lookup(LtGrandfatheredDb *grandfathereddb,
                                                  const char            *tag);

LT_END_DECLS

#endif /* __LT_GRANDFATHERED_DB_H__ */
