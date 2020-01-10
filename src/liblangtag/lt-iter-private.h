/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-iter-private.h
 * Copyright (C) 2011-2015 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifndef __LT_ITER_PRIVATE_H__
#define __LT_ITER_PRIVATE_H__

#if !defined (__LANGTAG_PRIVATE)
#error "Unable to use the private header publicly"
#endif

#include "lt-mem.h"
#include "lt-iter.h"

LT_BEGIN_DECLS

typedef lt_iter_t * (* lt_iter_init_func_t) (lt_iter_tmpl_t *tmpl);
typedef void        (* lt_iter_fini_func_t) (lt_iter_t      *iter);
typedef lt_bool_t   (* lt_iter_next_func_t) (lt_iter_t      *iter,
					     lt_pointer_t   *key,
					     lt_pointer_t   *value);

struct _lt_iter_tmpl_t {
	lt_mem_t            parent;
	int                 magic_code;
	lt_iter_init_func_t init;
	lt_iter_fini_func_t fini;
	lt_iter_next_func_t next;
};
struct _lt_iter_t {
	lt_iter_tmpl_t *target;
};


#define LT_ITER_TMPL_INIT(_instance_, _prefix_)			\
	LT_STMT_START {						\
		lt_iter_tmpl_init((_instance_));		\
		(_instance_)->init = _prefix_ ## _iter_init;	\
		(_instance_)->fini = _prefix_ ## _iter_fini;	\
		(_instance_)->next = _prefix_ ## _iter_next;	\
	} LT_STMT_END

void lt_iter_tmpl_init(lt_iter_tmpl_t *tmpl);

LT_END_DECLS

#endif /* __LT_ITER_PRIVATE_H__ */
