#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-script-db.h
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

#ifndef __LT_SCRIPT_DB_H__
#define __LT_SCRIPT_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-script.gir.h>

LT_BEGIN_DECLS

/**
 * LtScriptDb:
 *
 * All the fields in the <structname>LtScriptDb</structname>
 * structure are private to the #LtScriptDb implementation.
 */
typedef struct _LtScriptDb	LtScriptDb;


LtScriptDb *lt_script_db_new        (void);
LtScriptDb *lt_script_db_ref        (LtScriptDb *scriptdb);
void            lt_script_db_unref      (LtScriptDb *scriptdb);
LtScript    *lt_script_db_lookup     (LtScriptDb *scriptdb,
                                         const char     *subtag);

LT_END_DECLS

#endif /* __LT_SCRIPT_DB_H__ */
