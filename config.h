/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Aug  8 18:37:51 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#ifndef DEFAULT_PORT
#warning DEFAULT_PORT has not been defined in Makefile.
#define DEFAULT_PORT	6667
#endif

#define FLAG_SHOWVERSION	(1 << 0)
#define FLAG_DEBUG			(1 << 1)
#define FLAG_HELP			(1 << 2)

struct config {
	char	*cfg_libdir;
	char	*cfg_package;
	char	*cfg_version;
	int		cfg_flags;
	char	*cfg_host;
	char	*cfg_port;
	char	*cfg_script;
}; /* struct config */

extern struct config config;

void show_config(void);

#endif /* _CONFIG_H */
