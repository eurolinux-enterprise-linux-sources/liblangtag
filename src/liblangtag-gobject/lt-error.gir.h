#include <glib.h>
/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-error.h
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

#ifndef __LT_ERROR_H__
#define __LT_ERROR_H__

#include <liblangtag-gobject/lt-macros.gir.h>

LT_BEGIN_DECLS

/**
 * LtErrorType:
 * @LT_ERR_UNKNOWN: unknown error happened.
 * @LT_ERR_SUCCESS: an operation is succeeded.
 * @LT_ERR_OOM: Out of memory occurred.
 * @LT_ERR_FAIL_ON_XML: an error happened in libxml2.
 * @LT_ERR_EOT: No tokens to scan.
 * @LT_ERR_FAIL_ON_SCANNER: an error happened in the scanner.
 * @LT_ERR_NO_TAG: No tags to process.
 * @LT_ERR_INVALID: Invalid operation.
 * @LT_ERR_ANY: No real error, but just a flag to query all of errors or ask
 *              if any errors happen
 *
 * Error code used in this library.
*/
enum _LtErrorType {
	LT_ERR_UNKNOWN = -1,
	LT_ERR_SUCCESS = 0,
	LT_ERR_OOM,
	LT_ERR_FAIL_ON_XML,
	LT_ERR_EOT,
	LT_ERR_FAIL_ON_SCANNER,
	LT_ERR_NO_TAG,
	LT_ERR_INVALID,
	LT_ERR_ANY
};

/**
 * LtError:
 *
 * All the fields in the <structname>LtError</structname>
 * structure are private to the #LtError implementation.
 */
typedef struct _LtError	LtError;
typedef enum _LtErrorType	LtErrorType;

LtError *lt_error_new   (void);
LtError *lt_error_ref   (LtError       *error);
void        lt_error_unref (LtError       *error);
LtError *lt_error_set   (LtError      **error,
			    LtErrorType   type,
                            const char       *message,
			    ...) LT_GNUC_PRINTF (3, 4);
void        lt_error_clear (LtError       *error);
LtBool   lt_error_is_set(LtError       *error,
			    LtErrorType   type);
void        lt_error_print (LtError       *error,
			    LtErrorType   type);

LT_END_DECLS

#endif /* __LT_ERROR_H__ */
