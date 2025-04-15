#ifndef LLIST_H
#define LLIST_H
#include "structs.h"

typedef struct Linked_List {
  HT_Node *head;
  HT_Node *tail;
  int length;
} Linked_List;

void ll_push_front(Linked_List *, void *);
void ll_push_back(Linked_List *, void *);
Linked_List *ll_init(void);
void *ll_front(const Linked_List *);
void *ll_back(const Linked_List *);
void ll_delete(Linked_List *, const int);
void ll_print(const Linked_List *);
void ll_free_list(Linked_List *);

#endif