/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Aug  9 18:05:16 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#ifndef _CALLBACKP_H
#define _CALLBACKP_H

#include <pthread.h>

#include "callback.h"
#include "lists.h"

struct cb_list_node {
	pthread_t		cl_thrd; /* thread executing this list (0 for none) */
	pthread_mutex_t	cl_mtx; /* to protect multithread access. */
	LNODE_T			cl_lst; /* the list */
	void *			cl_dat; /* list data. Initialized at list creation. */
}; /* struct cb_list_node */
	
struct cb_reg_node {
	int				cr_flags;
	cb_callback 	cr_callback;
	cb_list			cr_list;
	void *			cr_data;
	LNODE_T			cr_node;
}; /* struct cb_reg_node */

#endif /* _CALLBACKP_H */
