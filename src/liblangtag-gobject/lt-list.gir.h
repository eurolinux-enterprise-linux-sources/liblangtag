#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-list.h
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

#ifndef __LT_LIST_H__
#define __LT_LIST_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtList:
 *
 * All the fields in the <structname>LtList</structname>
 * structure are private to the #LtList implementation.
 */
typedef struct _LtList	LtList;

LtList    *lt_list_new        (void);
LtList    *lt_list_ref        (LtList          *list);
void          lt_list_unref      (LtList          *list);
void          lt_list_free       (LtPointer        data);
LtList    *lt_list_first      (LtList          *list);
LtList    *lt_list_last       (LtList          *list);
LtList    *lt_list_previous   (const LtList    *list);
LtList    *lt_list_next       (const LtList    *list);
LtPointer  lt_list_value      (const LtList    *list);
gsize        lt_list_length     (const LtList    *list);
LtList    *lt_list_append     (LtList          *list,
                                  LtPointer        data,
                                  LtDestroyFunc   func);
LtList    *lt_list_prepend    (LtList          *list,
				  LtPointer        data,
				  LtDestroyFunc   func);
LtList    *lt_list_remove     (LtList          *list,
                                  LtPointer        data);
LtList    *lt_list_delete     (LtList          *list,
				  LtPointer        data);
LtList    *lt_list_delete_link(LtList          *list,
				  LtList          *link_);
LtList    *lt_list_find       (LtList          *list,
                                  const LtPointer  data);
LtList    *lt_list_find_custom(LtList          *list,
                                  const LtPointer  data,
                                  LtCompareFunc   func);
LtList    *lt_list_sort       (LtList          *list,
				  LtCompareFunc   func);
LtList    *lt_list_pop        (LtList          *list,
				  LtPointer       *data);

LT_END_DECLS

#endif /* __LT_LIST_H__ */
