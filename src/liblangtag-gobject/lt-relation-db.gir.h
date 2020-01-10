#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-relation-db.h
 * Copyright (C) 2015 Akira TAGOH
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

#ifndef __LT_RELATION_DB_H__
#define __LT_RELATION_DB_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtRelationDb:
 *
 * All the fields in the <structname>LtRelationDb</structname>
 * structure are private to the #LtRelationDb implementation.
 */
typedef struct _LtRelationDb	LtRelationDb;


LtRelationDb *lt_relation_db_new                    (void);
LtRelationDb *lt_relation_db_ref                    (LtRelationDb  *relationdb);
void              lt_relation_db_unref                  (LtRelationDb  *relationdb);
LtList        *lt_relation_db_lookup_lang_from_script(LtRelationDb  *relationdb,
                                                         const LtScript *script);
LtList        *lt_relation_db_lookup_script_from_lang(LtRelationDb  *relationdb,
                                                         const LtLang   *lang);

LT_END_DECLS

#endif /* __LT_RELATION_DB_H__ */
