#ifndef LLIST_H
#define LLIST_H

#include "structs.h"

typedef struct Linked_List {
  HT_Node *head;
  HT_Node *tail;
} Linked_List;

Linked_List *ll_init(void);
void ll_push_front(Linked_List *, HT_Node *);
void *ll_get_key(const Linked_List *, void *);
void ll_print(const Linked_List *, char *(*print_with)(void *));
void ll_free_list(Linked_List *, void (*free_with)(void *pair));

#endif