/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Aug  9 11:07:47 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <assert.h>
#include <stdio.h>

#include "input_cb.h"
#include "debug.h"
#include "config.h"

void input_cb(struct message *m)
{
	int i;

	assert(m->cmd != NULL);
	printf("\n");
	if (m->org)
		printf(D("ORIGEN : %s\n"), m->org);
	printf(D("COMANDO: [%s]\n"), m->cmd);
	for (i = 0; i < m->argc; i++)
		printf(D("ARG #%i : \"%s\"\n"), i, m->argv[i]);

	assert(m->argv[i] == NULL);
} /* input_cb */
