#include "structs.h"
#ifndef LLIST_H   /* Include guard */
#define LLIST_H

void ll_add_to_start (Linked_List *, Node*);
void ll_add_to_end (Linked_List *, Node*);
Linked_List *ll_init(void);
void* ll_get_key(Linked_List *, Node*);
void ll_delete (Linked_List *, int index);
void ll_print (Linked_List *);
void ll_free_list (Linked_List *);

#endif