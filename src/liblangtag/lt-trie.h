/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-trie.h
 * Copyright (C) 2011-2012 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifndef __LT_TRIE_H__
#define __LT_TRIE_H__

#include <liblangtag/lt-macros.h>
#include <liblangtag/lt-iter.h>
#include <liblangtag/lt-list.h>
#include <liblangtag/lt-string.h>

LT_BEGIN_DECLS

typedef struct _lt_trie_t	lt_trie_t;
typedef struct _lt_trie_iter_t  lt_trie_iter_t;

lt_trie_t      *lt_trie_new        (void);
lt_trie_t      *lt_trie_ref        (lt_trie_t         *trie);
void            lt_trie_unref      (lt_trie_t         *trie);
lt_bool_t       lt_trie_add        (lt_trie_t         *trie,
                                    const char        *key,
                                    lt_pointer_t       data,
                                    lt_destroy_func_t  func);
lt_bool_t       lt_trie_replace    (lt_trie_t         *trie,
                                    const char        *key,
                                    lt_pointer_t       data,
                                    lt_destroy_func_t  func);
lt_bool_t       lt_trie_remove     (lt_trie_t         *trie,
                                    const char        *key);
lt_pointer_t    lt_trie_lookup     (lt_trie_t         *trie,
                                    const char        *key);
lt_list_t      *lt_trie_keys       (lt_trie_t         *trie);
lt_trie_iter_t *lt_trie_iter_init  (lt_trie_iter_t    *iter,
				    lt_trie_t         *trie);
void            lt_trie_iter_finish(lt_trie_iter_t    *iter);
lt_bool_t       lt_trie_iter_next  (lt_trie_iter_t    *iter,
				    lt_pointer_t      *key,
				    lt_pointer_t      *value);

LT_END_DECLS

#endif /* __LT_TRIE_H__ */
