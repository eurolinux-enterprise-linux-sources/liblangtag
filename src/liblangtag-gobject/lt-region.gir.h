#include <glib.h>
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

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtRegion:
 *
 * All the fields in the <structname>LtRegion</structname>
 * structure are private to the #LtRegion implementation.
 */
typedef struct _LtRegion	LtRegion;


LtRegion *lt_region_ref              (LtRegion       *region);
void         lt_region_unref            (LtRegion       *region);
const char  *lt_region_get_name         (const LtRegion *region);
const char  *lt_region_get_better_tag   (const LtRegion *region);
const char  *lt_region_get_tag          (const LtRegion *region);
const char  *lt_region_get_preferred_tag(const LtRegion *region);
void         lt_region_dump             (const LtRegion *region);
LtBool    lt_region_compare          (const LtRegion *v1,
					 const LtRegion *v2);

LT_END_DECLS

#endif /* __LT_REGION_H__ */
