#include "llist.h"
#include "compare.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
ll_add_to_start (Linked_List *list, Node *node)
{
  node->next = list->head;
  list->head = node;

  if (list->length == 0)
    {
      list->tail = list->head;
    }

  list->length++;
}

void
ll_add_to_end (Linked_List *list, Node *node)
{
  Node *current = list->tail;

  current->next = node;
  list->tail = current->next;

  current->next->next = NULL;

  list->length++;
}

Linked_List *
ll_init (void)
{
  Linked_List *list = calloc (1, sizeof (Linked_List));
  if (!list)
    {
      perror ("ll_init: failed to allocate memory for linked list");
      exit (EXIT_FAILURE);
    }

  if (!list)
    {
      return NULL;
    }
  list->length = 0;
  list->head = NULL;
  list->tail = list->head;

  return list;
}

void *
ll_get_key (Linked_List *list, Node *node)
{
  Node *current = list->head;

  while (current != NULL)
    {
      if (compare_key (current, node->pair->Key) == 0)
        return current->pair->Value;

      current = current->next;
    }
  return NULL;
}

void
ll_print (Linked_List *list)
{
  Node *current = list->head;
  int len = list->length;

  if (len == 0)
    {
      return;
    }

  do
    {
      printf ("[%p]->", (void *)current);
      if (current->next == NULL)
        printf ("%p", (void *)current->next);
      current = current->next;
    }
  while (--len);
}

void
ll_free_list (Linked_List *list)
{
  Node *current = list->head;

  while (current != NULL)
    {
      if (current->pair->Key != NULL && current->key_type == STRING)
        {
          free (current->pair->Key);
        }
      if (current->pair->Value != NULL
          && infer_type (current->pair->Value) == STRING)
        {
          free (current->pair->Value);
        }
      Node *nextNode = current->next;
      free (current->pair);
      free (current);
      current = nextNode;
    }
  free (list);
}