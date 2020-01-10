#ifndef __LT_CONFIG_H__
#define __LT_CONFIG_H__

#ifdef __cplusplus
#define LT_HAVE_INLINE	1
#else /* !__cplusplus */
#define LT_HAVE_INLINE	1
#define LT_HAVE__INLINE	1
#define LT_HAVE__INLINE__	1
#endif /* !__cplusplus */

#ifdef __cplusplus
#define LT_CAN_INLINE	1
#endif

#include <liblangtag/lt-macros.h>

#endif /* __LT_CONFIG_H__ */
