/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Aug  8 18:39:03 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <stdio.h>

#include "config.h"
#include "debug.h"

#ifndef PREFIX
#error PREFIX must be defined to compile this module.
#endif
#ifndef PACKAGE
#error PACKAGE must be defined to compile this module.
#endif
#ifndef VERSION
#error VERSION must be defined to compile this module.
#endif

struct config config = {
	.cfg_libdir		= PREFIX "/lib/" PACKAGE,
	.cfg_package	= PACKAGE,
	.cfg_version	= VERSION,
	.cfg_flags		= FLAG_DEBUG,
	.cfg_host		= "localhost",
	.cfg_port		= "irc",
	.cfg_script		= ".rcircbot",
}; /* config */

void show_config(void)
{
#define STR "\"%s\""
#define HEX	"%#010x"
	TR(STR, char *,	config.cfg_libdir);
	TR(STR, char *,	config.cfg_version);
	TR(HEX,	int,	config.cfg_flags);
	TR(STR, char *,	config.cfg_host);
	TR(STR, char *,	config.cfg_port);
	TR(STR, char *,	config.cfg_script);
} /* show_config */
