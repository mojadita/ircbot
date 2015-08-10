/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Aug 10 17:27:20 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <assert.h>
#include <avl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "atoms.h"

static AVL_TREE atom_db;

struct node {
	size_t		a_ntimes;
	const char *a_str;
};

const char *intern(const char *a)
{
	struct node *n;
	if (!atom_db) {
		assert(atom_db = new_avl_tree(
                    (AVL_FCOMP) strcmp,
                    (AVL_FCONS) strdup,
                    (AVL_FDEST) free,
                    (AVL_FPRNT) fputs));
	} /* if */
	n = avl_tree_get(atom_db, a);
	if (!n) {
		AVL_ITERATOR p;
		assert(n = malloc(sizeof(struct node)));
		p = avl_tree_put(atom_db, a, n);
		n->a_ntimes = 0;
		n->a_str = avl_iterator_key(p);
	} /* if */
	n->a_ntimes++;
	return n->a_str;
} /* intern */

size_t pratom_db(FILE *out)
{
	AVL_ITERATOR i;
	size_t res = 0;
	for (i = avl_tree_first(atom_db);
		 i;
		 i = avl_iterator_next(i))
	{
		struct node *p = avl_iterator_data(i);
		res += printf(D("[%#p](%6llu): \"%s\"\n"),
			p->a_str, p->a_ntimes, p->a_str);
	} /* for */
	return res;
} /* pratom_db */
