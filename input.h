/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: jue jul 30 17:26:10 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */
#ifndef _INPUT_H
#define _INPUT_H

#include <sys/types.h>

#define BUFFSIZE	1024
#define MAX_ARGS	128

/* automaton states */
enum status {
	AT_BOM,
	IN_ORG,
	IN_SPC0,
	IN_CMD,
	IN_SPC1,
	IN_ARG,
	IN_ARGN,
	IN_EOL,
}; /* enum status */

struct message {
	char		buffer[BUFFSIZE];
	enum status	status;
	size_t		sz, argc;
	char		*p,
				*org,
				*cmd,
				*argv[MAX_ARGS];
	void (*cb)(struct message *);
};

void input(FILE *fd, struct message *p);

#endif /* _INPUT_H */
