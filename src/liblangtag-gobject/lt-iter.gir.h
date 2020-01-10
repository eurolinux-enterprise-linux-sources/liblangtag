#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-iter.h
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

#ifndef __LT_ITER_H__
#define __LT_ITER_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LT_ITER_INIT:
 * @_obj_: an object that initialize the iterator with.
 *
 * This is a convenient macro to call lt_iter_init().
 *
 * Returns: (transfer full): a #LtIter.
 */
#define LT_ITER_INIT(_obj_)	lt_iter_init((LtIterTmpl *)(_obj_))

/**
 * LtIterTmpl:
 *
 * All the fields in the <structname>LtIterTmpl</structname>
 * structure are private to the #LtIterTmpl implementation.
 */
typedef struct _LtIterTmpl	LtIterTmpl;
/**
 * LtIter:
 *
 * All the fields in the <structname>LtIter</structname>
 * structure are private to the #LtIter implementation.
 */
typedef struct _LtIter	LtIter;

LtIter *lt_iter_ref   (LtIter      *iter);
void       lt_iter_unref (LtIter      *iter);
LtIter *lt_iter_init  (LtIterTmpl *tmpl);
void       lt_iter_finish(LtIter      *iter);
LtBool  lt_iter_next  (LtIter      *iter,
                          LtPointer   *key,
                          LtPointer   *val);

LT_END_DECLS

#endif /* __LT_ITER_H__ */
