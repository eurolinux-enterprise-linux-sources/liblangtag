#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-string.h
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

#ifndef __LT_STRING_H__
#define __LT_STRING_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <sys/types.h>

LT_BEGIN_DECLS

/**
 * LtString:
 *
 * All the fields in the <structname>LtString</structname>
 * structure are private to the #LtString implementation.
 */
typedef struct _LtString	LtString;

LtString *lt_string_new            (const char        *string);
LtString *lt_string_ref            (LtString       *string);
void         lt_string_unref          (LtString       *string);
char        *lt_string_free           (LtString       *string,
                                       LtBool          free_segment);
gsize       lt_string_length         (const LtString *string);
const char  *lt_string_value          (const LtString *string);
LtString *lt_string_truncate       (LtString       *string,
                                       gssize            len);
void         lt_string_clear          (LtString       *string);
LtString *lt_string_append_c       (LtString       *string,
                                       char               c);
LtString *lt_string_append         (LtString       *string,
                                       const char        *str);
LtString *lt_string_append_filename(LtString       *string,
                                       const char        *path,
				       ...) LT_GNUC_NULL_TERMINATED;
void         lt_string_append_printf  (LtString       *string,
                                       const char        *format,
				       ...) LT_GNUC_PRINTF (2, 3);
LtString *lt_string_replace_c      (LtString       *string,
                                       gsize             pos,
                                       char               c);
char         lt_string_at             (LtString       *string,
                                       gssize            pos);

LT_END_DECLS

#endif /* __LT_STRING_H__ */
