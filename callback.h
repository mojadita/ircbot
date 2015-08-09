/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Aug  9 18:05:16 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#ifndef _CALLBACK_H
#define _CALLBACK_H

#include "lists.h"

/* THIS FLAG MAKES THE CALLBACK CALLING PROCESS TO ABORT
 * IF THE CALLBACK CALLED RETURNS A NONZERO STATUS. */
#define CB_ONERR_ABORT		(1 << 0)

/* THIS FLAG MAKES THE RETURN VALUE FROM THE CALLBACK TO
 * BE IGNORED AND NOT TO BE ADDED IN THE RESULT. */
#define CB_ONERR_IGNORE		(1 << 1)

/* THIS FLAG IS THE RESULT OF A PREVIOUS cb_unregister CALL.
 * THE cb_execute ROUTINE JUSTS SKIPS THE REGISTER AND
 * DELETES THE struct cb_reg_s ASSOCIATED. */
#define CB_UNREGISTERED		(1 << 2)

#define CB_REGISTER_INSERT	(1 << 3)

typedef struct cb_list_node	*cb_list;
typedef struct cb_reg_node	*cb_reg;
typedef int (*cb_callback)(
	cb_list		list_id, /* list id for this callback */
	cb_reg		reg_id, /* register id of the callback */
	void *		list_data, /* list data. */
	void *		reg_data, /* registered data */
	void *		call_data); /* call data */

cb_list cb_new(void *list_private_data);
void cb_free(cb_list list_id);

cb_reg cb_register(
	cb_list		list_id,
	cb_callback	callback_pointer,
	void *		registry_private_data,
	int			flags);

void cb_unregister(
	cb_reg		reg_id);

int cb_execute(
	cb_list		list_id,
	void *		call_data);

#endif /* _CALLBACK_H */
