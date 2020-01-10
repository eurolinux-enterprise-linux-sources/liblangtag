#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-lang-db.h
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

#ifndef __LT_LANG_DB_H__
#define __LT_LANG_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-iter.gir.h>
#include <liblangtag-gobject/lt-lang.gir.h>

LT_BEGIN_DECLS

/**
 * LtLangDb:
 *
 * All the fields in the <structname>LtLangDb</structname>
 * structure are private to the #LtLangDb implementation.
 */
typedef struct _LtLangDb		LtLangDb;

LtLangDb *lt_lang_db_new   (void);
LtLangDb *lt_lang_db_ref   (LtLangDb *langdb);
void          lt_lang_db_unref (LtLangDb *langdb);
LtLang    *lt_lang_db_lookup(LtLangDb *langdb,
                                const char   *subtag);

LT_END_DECLS

#endif /* __LT_LANG_DB_H__ */
