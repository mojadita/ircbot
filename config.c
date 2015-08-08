/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Aug  8 18:39:03 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include "config.h"

#ifndef PREFIX
#define PREFIX "/usr/local"
#endif

struct config config = {
	.cfg_libdir = PREFIX "/lib",
}; /* config */
