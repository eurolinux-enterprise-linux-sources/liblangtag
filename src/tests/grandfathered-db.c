/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * grandfathered.c
 * Copyright (C) 2011-2012 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <locale.h>
#include "langtag.h"
#include "lt-utils.h"

int
main(int    argc,
     char **argv)
{
	lt_grandfathered_db_t *grandfathereddb;
	lt_grandfathered_t *grandfathered;

	setlocale(LC_ALL, "");

	lt_db_set_datadir(TEST_DATADIR);
	grandfathereddb = lt_grandfathered_db_new();

	if (lt_strcmp0(argv[1], "list_keys") == 0) {
		const char *key;
		lt_iter_t *iter;

		iter = LT_ITER_INIT (grandfathereddb);
		while (lt_iter_next(iter,
				    (lt_pointer_t *)&key,
				    NULL)) {
			printf("%s\n", key);
		}
		lt_iter_finish(iter);
	} else if (lt_strcmp0(argv[1], "list_values") == 0) {
		lt_iter_t *iter;

		iter = LT_ITER_INIT (grandfathereddb);
		while (lt_iter_next(iter,
				    NULL,
				    (lt_pointer_t *)&grandfathered)) {
			lt_grandfathered_dump(grandfathered);
		}
		lt_iter_finish(iter);
	} else if (lt_strcmp0(argv[1], "lookup") == 0) {
		grandfathered = lt_grandfathered_db_lookup(grandfathereddb, argv[2]);

		if (grandfathered) {
			printf("desc: %s\n", lt_grandfathered_get_name(grandfathered));
			lt_grandfathered_unref(grandfathered);
		} else {
			printf("no such grandfathered: %s\n", argv[2]);
		}
	}

	lt_grandfathered_db_unref(grandfathereddb);

	return 0;
}
