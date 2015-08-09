/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Aug  9 19:33:22 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <stdlib.h>
#include "callbackP.h"
#include "debug.h"

cb_list cb_new(void *private_data)
{
	cb_list res = malloc(sizeof (struct cb_list_node));
	if (!res) return NULL;
	pthread_mutex_init(&res->cl_mtx, NULL);
	LIST_INIT(&res->cl_lst);
	res->cl_dat = private_data;

	return res;
} /* cb_init */

void cb_free(cb_list list)
{
	cb_reg p;

	pthread_mutex_lock(&list->cl_mtx);
	while (p = LIST_FIRST_ELEMENT(&list->cl_lst, struct cb_reg_node, cr_node)) {
		LIST_DELETE(&p->cr_node);
		free(p);
	} /* while */
	pthread_mutex_unlock(&list->cl_mtx);
	free(list);
} /* cb_free */

cb_reg
cb_register(
	cb_list			l,
	cb_callback	    cb,
	void *			private_data,
	int				flags)
{
	cb_reg res = malloc(sizeof (struct cb_reg_node));
	if (!res) return NULL;
	res->cr_flags = flags & ~CB_UNREGISTERED & ~CB_REGISTER_INSERT;
	res->cr_callback = cb;
	res->cr_list = l;
	res->cr_data = private_data;
	pthread_mutex_lock(&l->cl_mtx);
	if (flags & CB_REGISTER_INSERT)
		LIST_INSERT(&l->cl_lst, &res->cr_node);
	else
		LIST_APPEND(&l->cl_lst, &res->cr_node);
	pthread_mutex_unlock(&l->cl_mtx);
	return res;
} /* cb_register */

void
cb_unregister(
	cb_reg reg_id)
{
	reg_id->cr_flags |= CB_UNREGISTERED;
} /* cb_unregister */


int
cb_execute(
	cb_list 		l,
	void *			call_data)
{
	struct cb_reg_node *p;
	int res = 0;

	pthread_mutex_lock(&l->cl_mtx);
    p = LIST_FIRST_ELEMENT(&l->cl_lst, struct cb_reg_node, cr_node);
    while (p) {
        struct cb_reg_node *q = LIST_NEXT_ELEMENT(p, &l->cl_lst, struct cb_reg_node, cr_node);
        if (p->cr_callback && !(p->cr_flags & CB_UNREGISTERED)) {
            int local_res = p->cr_callback(l, p, l->cl_dat, p->cr_data, call_data);
            if ((p->cr_flags & CB_ONERR_IGNORE) == 0) res |= local_res;
            if ((p->cr_flags & CB_ONERR_ABORT) && local_res) break;
		} /* if */
        if (p->cr_flags & CB_UNREGISTERED) {
            LIST_DELETE(&p->cr_node);
            free(p);
        } /* if */
        p = q;
	} /* LIST_FOREACH_ELEMENT */
	pthread_mutex_unlock(&l->cl_mtx);
	return res;
} /* cb_execute */
