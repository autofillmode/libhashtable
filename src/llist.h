#ifndef LLIST_H
#define LLIST_H

#include "structs.h"

typedef struct Linked_List {
  HT_Node *head;
  HT_Node *tail;
  int length;
} Linked_List;

Linked_List *ll_init(void);
void ll_push_front(Linked_List *, void *);
void ll_push_back(Linked_List *, void *);
void *ll_front(const Linked_List *);
void *ll_back(const Linked_List *);
void *ll_get_key(const Linked_List *, HT_TYPE, void *);
void ll_print(const Linked_List *, char *(*print_with)(void *));
void ll_delete(Linked_List *, const int, void (*free_with)(void *));
void ll_free_list(Linked_List *, void (*free_with)(void *));

#endif