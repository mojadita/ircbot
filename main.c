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

	while ((opt = getopt(argc, argv, "VL:")) != EOF) {
		switch (opt) {
		case 'V': show_version(); break;
		case 'L': config.cfg_libdir = optarg; break;
		} /* switch */
	} /* while */
#define P(fmt, X) printf(#X": " fmt "\n", (X))
	P("%s", config.cfg_libdir);
	exit(EXIT_SUCCESS);
}
