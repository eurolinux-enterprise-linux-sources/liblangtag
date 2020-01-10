/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-extlang-private.h
 * Copyright (C) 2011-2012 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifndef __LT_EXTLANG_PRIVATE_H__
#define __LT_EXTLANG_PRIVATE_H__

#include "lt-macros.h"
#include "lt-extlang.h"

LT_BEGIN_DECLS

lt_extlang_t *lt_extlang_create            (void);
void          lt_extlang_set_tag           (lt_extlang_t *extlang,
                                            const char   *subtag);
void          lt_extlang_set_preferred_tag (lt_extlang_t *extlang,
                                            const char   *subtag);
void          lt_extlang_set_name          (lt_extlang_t *extlang,
                                            const char   *description);
void          lt_extlang_set_macro_language(lt_extlang_t *extlang,
                                            const char   *macrolanguage);
void          lt_extlang_add_prefix        (lt_extlang_t *extlang,
                                            const char   *prefix);

LT_END_DECLS

#endif /* __LT_EXTLANG_PRIVATE_H__ */
