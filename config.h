/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Aug  8 18:37:51 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#define FLAG_SHOWVERSION	(1 << 0)
#define FLAG_DEBUG			(1 << 1)

struct config {
	char	*cfg_libdir;
	char	*cfg_package;
	char	*cfg_version;
	int		cfg_flags;
}; /* struct config */

extern struct config config;

#endif /* _CONFIG_H */
