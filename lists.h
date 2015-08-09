/* $Id: lists.h.in,v 1.4 2007/04/25 22:35:33 luis Exp $
 * Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: Mon Jul 18 17:21:22 CEST 2005
 *
 * Disclaimer:
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Do not include anything BEFORE the line below, as it would not be
 * protected against double inclusion from other files
 */
#ifndef LISTS_H
#define LISTS_H

static char LISTS_H_RCSId[] = "\n$Id: lists.h.in,v 1.4 2007/04/25 22:35:33 luis Exp $\n";

#define LISTS_H_PACKAGE_NAME "lists"
#define LISTS_H_PACKAGE_VERSION "0.4"
#define LISTS_H_PACKAGE_STRING "lists 0.4"

/* constants */

/* types */
typedef struct LNODE_S {
		struct LNODE_S *prev;
		struct LNODE_S *next;
} LNODE_T, *LNODE_P;

/* definitions */
#ifndef OFFSETOF
#define OFFSETOF(X,f) ((char*)&(((X*)0)->f)-(char*)0)
#endif

#define LIST_INIT(X) do{(X)->prev=(X)->next=(X);}while(0)
#define LIST_DECLARE(X) LNODE_T X={.next=&X,.prev=&X}

#define LIST_EMPTY(L) ((L)->next==(L))

#define LIST_FIRST(X) (LIST_EMPTY(X)?0:(X)->next)
#define LIST_LAST(X) (LIST_EMPTY(X)?0:(X)->prev)
#define LIST_NEXT(X) LIST_FIRST(X)
#define LIST_PREV(X) LIST_LAST(X)

#define LIST_ATEOL(p,L) ((p)==(L))
#define LIST_FOREACH(p,L) for(p=LIST_FIRST(L);!LIST_ATEOL(p,L);p=LIST_NEXT(p))
#define LIST_FORBACK(p,L) for(p=LIST_LAST(L);!LIST_ATEOL(p,L);p=LIST_PREV(p))

#define LIST_ELEMENT(x,T,f) ((x)?(T*)((char*)(x)-OFFSETOF(T,f)):0)

#define LIST_FIRST_ELEMENT(L,T,f) LIST_ELEMENT(LIST_FIRST(L),T,f)
#define LIST_LAST_ELEMENT(L,T,f) LIST_ELEMENT(LIST_LAST(L),T,f)
#define LIST_NEXT_ELEMENT(e,L,T,f) (LIST_ATEOL(LIST_NEXT(&(e)->f),L)?0:LIST_ELEMENT(LIST_NEXT(&(e)->f),T,f))
#define LIST_PREV_ELEMENT(e,L,T,f) (LIST_ATEOL(LIST_PREV(&(x)->f),L)?0:LIST_ELEMENT(LIST_PREV(&(e)->f),T,f))

#define LIST_FOREACH_ELEMENT(p,L,T,f) for(p=LIST_FIRST_ELEMENT(L,T,f);p;p=LIST_NEXT_ELEMENT(p,L,T,f))
#define LIST_FORBACK_ELEMENT(p,L,T,f) for(p=LIST_LAST_ELEMENT(L,T,f);p;p=LIST_PREV_ELEMENT(p,L,T,f))

#define LIST_INSERT(L,p) do{(p)->next=(L)->next;(p)->prev=(L);(L)->next=(p);(p)->next->prev=(p);}while(0)
#define LIST_APPEND(L,p) do{(p)->prev=(L)->prev;(p)->next=(L);(L)->prev=(p);(p)->prev->next=(p);}while(0)
#define LIST_DELETE(p)   do{(p)->next->prev=(p)->prev;(p)->prev->next=(p)->next;}while(0)

#endif /* LISTS_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.
 */
/* $Id: lists.h.in,v 1.4 2007/04/25 22:35:33 luis Exp $ */
