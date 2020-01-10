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

#include <liblangtag/lt-macros.h>

LT_BEGIN_DECLS

/**
 * LT_ITER_INIT:
 * @_obj_: an object that initialize the iterator with.
 *
 * This is a convenient macro to call lt_iter_init().
 *
 * Returns: (transfer full): a #lt_iter_t.
 */
#define LT_ITER_INIT(_obj_)	lt_iter_init((lt_iter_tmpl_t *)(_obj_))

/**
 * lt_iter_tmpl_t:
 *
 * All the fields in the <structname>lt_iter_tmpl_t</structname>
 * structure are private to the #lt_iter_tmpl_t implementation.
 */
typedef struct _lt_iter_tmpl_t	lt_iter_tmpl_t;
/**
 * lt_iter_t:
 *
 * All the fields in the <structname>lt_iter_t</structname>
 * structure are private to the #lt_iter_t implementation.
 */
typedef struct _lt_iter_t	lt_iter_t;

lt_iter_t *lt_iter_ref   (lt_iter_t      *iter);
void       lt_iter_unref (lt_iter_t      *iter);
lt_iter_t *lt_iter_init  (lt_iter_tmpl_t *tmpl);
void       lt_iter_finish(lt_iter_t      *iter);
lt_bool_t  lt_iter_next  (lt_iter_t      *iter,
                          lt_pointer_t   *key,
                          lt_pointer_t   *val);

LT_END_DECLS

#endif /* __LT_ITER_H__ */
