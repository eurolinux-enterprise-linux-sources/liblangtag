/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-lang-private.h
 * Copyright (C) 2011-2012 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifndef __LT_LANG_PRIVATE_H__
#define __LT_LANG_PRIVATE_H__

#include "lt-macros.h"
#include "lt-lang.h"

LT_BEGIN_DECLS

lt_lang_t *lt_lang_create             (void);
void       lt_lang_set_name           (lt_lang_t  *lang,
                                       const char *description);
void       lt_lang_set_tag            (lt_lang_t  *lang,
                                       const char *subtag);
void       lt_lang_set_preferred_tag  (lt_lang_t  *lang,
                                       const char *subtag);
void       lt_lang_set_suppress_script(lt_lang_t  *lang,
                                       const char *script);
void       lt_lang_set_macro_language (lt_lang_t  *lang,
                                       const char *macrolanguage);
void       lt_lang_set_scope          (lt_lang_t  *lang,
                                       const char *scope);

LT_END_DECLS

#endif /* __LT_LANG_PRIVATE_H__ */
