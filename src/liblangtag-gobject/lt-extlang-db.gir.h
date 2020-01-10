#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-extlang-db.h
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

#ifndef __LT_EXTLANG_DB_H__
#define __LT_EXTLANG_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-extlang.gir.h>

LT_BEGIN_DECLS

/**
 * LtExtlangDb:
 *
 * All the fields in the <structname>LtExtlangDb</structname>
 * structure are private to the #LtExtlangDb implementation.
 */
typedef struct _LtExtlangDb	LtExtlangDb;


LtExtlangDb *lt_extlang_db_new   (void);
LtExtlangDb *lt_extlang_db_ref   (LtExtlangDb *extlangdb);
void             lt_extlang_db_unref (LtExtlangDb *extlangdb);
LtExtlang    *lt_extlang_db_lookup(LtExtlangDb *extlangdb,
                                      const char      *subtag);

LT_END_DECLS

#endif /* __LT_EXTLANG_DB_H__ */
