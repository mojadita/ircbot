/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Jul 30 18:31:15 EEST 2015
 * Copyright: (2015) LUIS COLORADO.  All rights reserved.
 */

#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <stdint.h>

#include "debug.h"
#include "config.h"

int main(int argc, char **argv)
{
	int opt;

	while ((opt = getopt(argc, argv, "VL:d")) != EOF) {
		switch (opt) {
		case 'V': config.cfg_flags |= FLAG_SHOWVERSION; break;
		case 'L': config.cfg_libdir = optarg; break;
		case 'd': config.cfg_flags |= FLAG_DEBUG; break;
		} /* switch */
	} /* while */

	if (config.cfg_flags & FLAG_SHOWVERSION) {
		printf(D("Version: %s\n"),
			config.cfg_version);
		exit(EXIT_SUCCESS);
	} /* if */

	if (config.cfg_flags & FLAG_DEBUG) {
#define P(fmt, X) printf(D(#X " = " fmt "\n"), X)
		P("%s", config.cfg_libdir);
		P("%s", config.cfg_version);
		P("%#x", config.cfg_flags);
#undef P
	} /* if */

	exit(EXIT_SUCCESS);
} /* main */
