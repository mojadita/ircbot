/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Aug 10 17:51:58 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atoms.h"
#include "debug.h"

int main()
{
	char buffer[1024];
	while (fgets(buffer, sizeof buffer, stdin)) {
		const char *s = intern(strtok(buffer, "\n"));
		printf(D("[%#p]: %s\n"), s, s);
	} /* while */
	pratom_db(stdout);
	return EXIT_SUCCESS;
} /* main */
