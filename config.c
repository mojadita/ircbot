/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Aug  8 18:39:03 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include "config.h"

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
	.cfg_flags		= 0,
}; /* config */
