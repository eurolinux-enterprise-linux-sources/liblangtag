#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-ext-module-data.h
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

#ifndef __LT_EXT_MODULE_DATA_H__
#define __LT_EXT_MODULE_DATA_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtExtModuleData:
 * @dummy: a dummy pointer for alignment.
 *
 * All the fields in the <structname>LtExtModuleData</structname>
 * structure are private to the #LtExtModuleData implementation.
 */
struct _LtExtModuleData {
	LtPointer dummy[8];
};

typedef struct _LtExtModuleData	LtExtModuleData;


LtExtModuleData *lt_ext_module_data_new  (gsize                size,
					       LtDestroyFunc     finalizer);
LtExtModuleData *lt_ext_module_data_ref  (LtExtModuleData *data);
void                  lt_ext_module_data_unref(LtExtModuleData *data);

LT_END_DECLS

#endif /* __LT_EXT_MODULE_DATA_H__ */
