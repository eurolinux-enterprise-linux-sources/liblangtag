/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-region.h
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

#ifndef __LT_REGION_H__
#define __LT_REGION_H__

#include <liblangtag/lt-macros.h>

LT_BEGIN_DECLS

/**
 * lt_region_t:
 *
 * All the fields in the <structname>lt_region_t</structname>
 * structure are private to the #lt_region_t implementation.
 */
typedef struct _lt_region_t	lt_region_t;


lt_region_t *lt_region_ref              (lt_region_t       *region);
void         lt_region_unref            (lt_region_t       *region);
const char  *lt_region_get_name         (const lt_region_t *region);
const char  *lt_region_get_better_tag   (const lt_region_t *region);
const char  *lt_region_get_tag          (const lt_region_t *region);
const char  *lt_region_get_preferred_tag(const lt_region_t *region);
void         lt_region_dump             (const lt_region_t *region);
lt_bool_t    lt_region_compare          (const lt_region_t *v1,
					 const lt_region_t *v2);

LT_END_DECLS

#endif /* __LT_REGION_H__ */
