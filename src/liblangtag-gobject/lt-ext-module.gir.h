#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-ext-mdule.h
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

#ifndef __LT_EXT_MODULE_H__
#define __LT_EXT_MODULE_H__

#include <liblangtag-gobject/lt-macros.gir.h>
#include <liblangtag-gobject/lt-error.gir.h>
#include <liblangtag-gobject/lt-ext-module-data.gir.h>
#include <liblangtag-gobject/lt-tag.gir.h>

LT_BEGIN_DECLS

/**
 * LT_EXT_MODULE_VERSION:
 *
 * Static variable for the module version. this is used to ensure if the built
 * module is compatible with the runtime library.
 */
#define LT_EXT_MODULE_VERSION		1

/**
 * LtExtModule:
 *
 * All the fields in the <structname>LtExtModule</structname>
 * structure are private to the #LtExtModule implementation.
 */
typedef struct _LtExtModule		LtExtModule;
typedef struct _LtExtModuleFuncs	LtExtModuleFuncs;

/**
 * LtExtModuleVersionFunc:
 *
 * The type of the module_get_version() that is required to implement
 * an extension module.
 *
 * Returns: a version number. this is the same to #LT_EXT_MODULE_VERSION
 *          when the module was built.
 */
typedef int                          (* LtExtModuleVersionFunc)   (void);
/**
 * LtExtModuleGetFuncsFunc:
 *
 * The type of the module_get_funcs() that is required to implement
 * an extension module.
 *
 * Returns: (transfer none): a #LtExtModuleFuncs.
 */
typedef const LtExtModuleFuncs * (* LtExtModuleGetFuncsFunc) (void);

/**
 * LtExtModuleSingletonFunc:
 *
 * The type of the callback function used to obtain a singleton character
 * for Extension subtag that the module would support.
 *
 * Returns: a singleton character.
 */
typedef char                  (* LtExtModuleSingletonFunc) (void);
/**
 * LtExtModuleDataNewFunc:
 *
 * The type of the callback function used to create a new instance of
 * #LtExtModuleData.
 * This is invoked when new Extension subtag appears and keep data.
 *
 * Returns: a new instance of #LtExtModuleData.
 */
typedef LtExtModuleData * (* LtExtModuleDataNewFunc)  (void);
/**
 * LtExtModulePrecheckFunc:
 * @data: a #LtExtModuleData.
 * @tag: a #LtTag.
 * @error: (allow-none): a #LtError.
 *
 * The type of the callback function used to check @tag prior to process
 * parsing subtags for the extension.
 *
 * Returns: %TRUE if @tag is valid to process parsing subtags for the extension.
 *          otherwise %FALSE.
 */
typedef LtBool (* LtExtModulePrecheckFunc)  (LtExtModuleData  *data,
						      const LtTag        *tag,
						      LtError           **error);
/**
 * LtExtModuleParseFunc:
 * @data: a #LtExtModuleData.
 * @subtag: a subtag string to parse.
 * @error: (allow-none): a #LtError.
 *
 * The type of the callback function used to parse tags.
 *
 * Returns: %TRUE if the @subtag is valid for Extension. otherwise %FALSE.
 */
typedef LtBool (* LtExtModuleParseFunc)     (LtExtModuleData  *data,
						      const char            *subtag,
						      LtError           **error);
/**
 * LtExtModuleGetTagFunc:
 * @data: a #LtExtModuleData.
 *
 * The type of the callback function used to obtain the tag.
 *
 * Returns: a tag string.
 */
typedef char * (* LtExtModuleGetTagFunc)   (LtExtModuleData *data);
/**
 * LtExtModuleValidateFunc:
 * @data: a #LtExtModuleData.
 *
 * The type of the callback function used to validate the tags in @data.
 *
 * Returns: %TRUE if it's valid, otherwise %FALSE.
 */
typedef LtBool (* LtExtModuleValidateFunc)  (LtExtModuleData *data);

/* For some yet unknown reason the MSVC compiler does not like the const
 * typedef'ed function pointers in the _LtExtModuleFuncs struct below. */
#ifdef _MSC_VER
#define LT_CONST_DECL
#else
#define LT_CONST_DECL const
#endif

/**
 * LtExtModuleFuncs:
 * @get_singleton: A callback function to obtain the singleton character
 *                 that are supposed in the module.
 * @create_data: A callback function to create a new instance of
 *               #LtExtModuleData for the module.
 * @precheck_tag: A callback function to check tags prior to parse subtags.
 * @parse_tag: A callback function to parse a tag.
 * @get_tag: A callback function to obtain the tag string.
 * @validate_tag: A callback function to validate the tag.
 *
 * The <structname>LtExtModuleFuncs</structname> struct is a callback
 * collection to provide an accessor between #lt_extension_t
 * and #LtExtModule and extend features.
 */
struct _LtExtModuleFuncs {
	LT_CONST_DECL LtExtModuleSingletonFunc get_singleton;
	LT_CONST_DECL LtExtModuleDataNewFunc  create_data;
	LT_CONST_DECL LtExtModulePrecheckFunc  precheck_tag;
	LT_CONST_DECL LtExtModuleParseFunc     parse_tag;
	LT_CONST_DECL LtExtModuleGetTagFunc   get_tag;
	LT_CONST_DECL LtExtModuleValidateFunc  validate_tag;
};


void             lt_ext_modules_load  (void);
void             lt_ext_modules_unload(void);
LtExtModule *lt_ext_module_ref    (LtExtModule *module);
void             lt_ext_module_unref  (LtExtModule *module);

#ifdef LT_MODULE_PREFIX
#  define LT_MODULE_SYMBOL(__sym__)		LT_MODULE_SYMBOL_(LT_MODULE_PREFIX, __sym__)
#else
#  define LT_MODULE_SYMBOL(__sym__)		module_##__sym__
#endif
#define LT_MODULE_SYMBOL_(__prefix__,__sym__)	LT_MODULE_SYMBOL__(__prefix__, __sym__)
#define LT_MODULE_SYMBOL__(__prefix__,__sym__)	__prefix__##_module_##__sym__

/**
 * module_get_version:
 *
 * Obtains the module version. this must be implemented in a module.
 *
 * Returns: a version number. this is the same to #LT_EXT_MODULE_VERSION
 *          when the module was built.
 */
int                          module_get_version(void);
/**
 * module_get_funcs:
 *
 * Obtains a #LtExtModuleFuncs, callback collection structure that
 * the module would process. this must be implemented in the external module.
 *
 * Returns: a #LtExtModuleFuncs.
 */
const LtExtModuleFuncs *module_get_funcs  (void);

LT_END_DECLS

#endif /* __LT_EXT_MODULE_H__ */
