/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: jue jul 30 17:26:10 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */
#ifndef _INPUT_H
#define _INPUT_H

#include <sys/types.h>
ssize_t input_msg(int fd, char *in, size_t sz);

#endif /* _INPUT_H */
