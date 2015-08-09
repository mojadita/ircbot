/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Aug  9 21:35:04 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "callback.h"
#include "debug.h"

int callback_routine(
	cb_list callback_list,
	cb_reg callback_reg,
	void *list_data,
	void *register_data,
	void *call_data)
{
	TR("%#p", cb_list, callback_list);
	TR("%#p", cb_reg, callback_reg);
	TR("%s", char *, list_data);
	TR("%s", char *, register_data);
	TR("%s", char *, call_data);
	return 1;
}

int callback_routine2(
	cb_list callback_list,
	cb_reg callback_reg,
	void *list_data,
	void *register_data,
	void *call_data)
{
	TR("%#p", cb_list, callback_list);
	TR("%#p", cb_reg, callback_reg);
	TR("%s", char *, list_data);
	TR("%s", char *, register_data);
	TR("%s", char *, call_data);
	cb_unregister(callback_reg);
	return 2;
}

int main()
{
	cb_list l, l2;

 	TR("%#p", cb_list, l = cb_new("cb_list l;"));
	TR("%#p", cb_list, l2 = cb_new("cb_list l2;"));
	TR("%#p", cb_reg, cb_register(l, callback_routine, "registro 1", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine, "registro 2", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine2, "registro 3", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine2, "registro 4", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine2, "registro 5", 0));
	TR("%#p", cb_reg, cb_register(l2, callback_routine, "registro 6", 0));
	TR("%#p", cb_reg, cb_register(l2, callback_routine, "registro 7", 0));
	TR("%#p", cb_reg, cb_register(l2, callback_routine2, "registro 8", 0));
	TR("%#p", cb_reg, cb_register(l2, callback_routine2, "registro 9", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine, "registro 10", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine2, "registro 11", 0));
	TR("%#p", cb_reg, cb_register(l, callback_routine, "registro 12", 0));
	TR("%#x", int, cb_execute(l, "ejecucion 1"));
	TR("%#x", int, cb_execute(l, "ejecucion 2"));
	TR("%#x", int, cb_execute(l2, "ejecucion 3"));
	TR("%#x", int, cb_execute(l2, "ejecucion 4"));
	TR("%#x", int, cb_execute(l2, "ejecucion 5"));
	TR("%#x", int, cb_execute(l, "ejecucion 6"));
	TR("%#x", int, cb_execute(l, "ejecucion 7"));

	return EXIT_SUCCESS;
} /* main */
