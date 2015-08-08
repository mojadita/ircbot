/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: jue jul 30 16:41:11 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "input.h"

void input(FILE *fd, struct message *p)
{
	int c;

#define ST(X) do { p->status = (X); } while(0)
#define MK(X) do { p->X = p->p; } while(0)
#define RST() do { \
	ST(AT_BOM); \
	p->p = p->buffer; \
	p->sz = p->argc = 0; \
	p->org = p->cmd = NULL; \
} while (0)
#define ADDCH(X) do { \
	*p->p++ = X; p->sz++; \
	if (p->sz >= (sizeof p->buffer)-1) \
		RST(); \
} while (0)
#define ADDARG(s) do { \
	assert(p->argc < MAX_ARGS); \
	p->argv[p->argc] = s; \
	if (s) p->argc++; \
} while (0)

	RST();
	while ((c = fgetc(fd)) != EOF) {
		switch (p->status) {
		case AT_BOM:
			switch (c) {
			case ':': ST(IN_ORG); MK(org); break;
			case ' ': break; /* ignored */
			case '\r': ST(IN_EOL); break;
			case '\n': RST(); break;
			default: ST(IN_CMD); MK(cmd); ADDCH(c); break;
			} break;
		case IN_ORG:
			switch(c) {
			case ' ': ST(IN_SPC0); ADDCH(0); break;
			case '\r': ST(IN_EOL); ADDCH(0); break;
			case '\n': RST(); break;
			case ':': /* NO BREAK HERE, valid char */
			default: ADDCH(c); break;
			} break;
		case IN_SPC0:
			switch(c) {
			case ' ': break; /* ignore extra */
			case '\r': ST(IN_EOL); break;
			case '\n': RST(); break;
			default: ST(IN_CMD); MK(cmd); ADDCH(c); break;
			} break;
		case IN_CMD:
			switch(c) {
			case ' ': ST(IN_SPC1); ADDCH(0); break;
			case '\r': ST(IN_EOL); ADDCH(0); break;
			case '\n': ADDARG(NULL); p->cb(p); RST(); break;
			case ':': /* NO BREAK HERE, valid char */
			default: ADDCH(c); break;
			} break;
		case IN_SPC1:
			switch(c) {
			case ' ': break; /* ignore */
			case '\r': ST(IN_EOL); break;
			case '\n': ADDARG(NULL); p->cb(p); RST(); break;
			case ':': ST(IN_ARGN); ADDARG(p->p); break;
			default: ST(IN_ARG); ADDARG(p->p); ADDCH(c); break;
			} break;
		case IN_ARG:
			switch (c) {
			case ' ': ST(IN_SPC1); ADDCH(0); break;
			case '\r': ST(IN_EOL); ADDCH(0); break;
			case '\n': ADDARG(NULL); p->cb(p); RST(); break;
			case ':':
			default: ADDCH(c); break;
			} break;
		case IN_ARGN:
			switch (c) {
			case '\r': ST(IN_EOL); ADDCH(0); break;
			case '\n': ADDARG(NULL); p->cb(p); RST(); break;
			default: ADDCH(c); break;
			} break;
		case IN_EOL:
			switch (c) {
			case '\r': break;
			case '\n': ADDARG(NULL); p->cb(p); RST(); break;
			case ':': RST(); ST(IN_ORG); break;
			default: RST(); break;
			} break;
		} /* switch */
	} /* while */
} /* input */

