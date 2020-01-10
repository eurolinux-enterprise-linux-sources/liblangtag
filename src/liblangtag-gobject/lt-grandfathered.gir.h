#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-grandfathered.h
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

#ifndef __LT_GRANDFATHERED_H__
#define __LT_GRANDFATHERED_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtGrandfathered:
 *
 * All the fields in the <structname>LtGrandfathered</structname>
 * structure are private to the #LtGrandfathered implementation.
 */
typedef struct _LtGrandfathered	LtGrandfathered;


LtGrandfathered *lt_grandfathered_ref              (LtGrandfathered       *grandfathered);
void                lt_grandfathered_unref            (LtGrandfathered       *grandfathered);
const char         *lt_grandfathered_get_better_tag   (const LtGrandfathered *grandfathered);
const char         *lt_grandfathered_get_tag          (const LtGrandfathered *grandfathered);
const char         *lt_grandfathered_get_preferred_tag(const LtGrandfathered *grandfathered);
const char         *lt_grandfathered_get_name         (const LtGrandfathered *grandfathered);
void                lt_grandfathered_dump             (const LtGrandfathered *grandfathered);
LtBool           lt_grandfathered_compare          (const LtGrandfathered *v1,
						       const LtGrandfathered *v2);

LT_END_DECLS

#endif /* __LT_GRANDFATHERED_H__ */
