#include "llist.h"
#include "compare.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static HT_Node *
ht_get_node (Node *node)
{
  return node->value;
}

/* Add a node to the head of the linked list. */
void
ll_push_front (Linked_List *list, void *val)
{
  Node *new = malloc (sizeof (Node));
  if (!new)
    {
      perror ("ll_add_: couldn't alloc memory for new node!");
      exit (EXIT_FAILURE);
    }
  new->value = val;

  new->next = list->head;
  list->head = new;

  if (list->length == 0)
    {
      list->tail = list->head;
    }

  list->length++;
}

/* Add a node to the tail of the linked list. If list is empty, calls
 * ll_push_front().
 */
void
ll_push_back (Linked_List *list, void *val)
{
  if (list->length == 0)
    {
      ll_push_front (list, val);
      return;
    }

  Node *current = list->tail;
  Node *new = malloc (sizeof (Node));
  if (!new)
    {
      perror ("ll_add_to_end: couldn't alloc memory for new node!");
      exit (EXIT_FAILURE);
    }

  new->value = val;

  current->next = new;
  list->tail = current->next;

  current->next->next = NULL;

  list->length++;
}

/* Initialize a new linked list */
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
ll_front (const Linked_List *list)
{
  if (list != NULL && list->head != NULL)
    {
      return list->head->value;
    }
  return NULL;
}

void *
ll_back (const Linked_List *list)
{
  if (list != NULL && list->tail != NULL)
    {
      return list->tail->value;
    }
  return NULL;
}

/* Print the whole linked list */
void
ll_print (const Linked_List *list)
{
  Node *current = list->head;
  int len = list->length;

  if (len == 0 || !list->head || !list)
    {
      return;
    }
  do
    {
      if (current)
        {
          printf ("[%s]->", (char *)ht_get_node (current)->pair->Value);
          current = current->next;
        }
    }
  while (--len);
  printf ("(null)");
}

void
ll_delete (Linked_List *list, const int index)
{
  if (index == 0)
    {
      Node *new_head = list->head->next;
      free (list->head);
      list->head = new_head;
    }
  else
    {
      Node *current = list->head;
      int i = 0;
      while (current != list->tail || i++ < index)
        {
          if (current->next == list->tail || i == index - 1)
            {
              if (i == index)
                {
                  current->next = current->next->next;
                  free (current->next);
                }
              free (list->tail);
              list->tail = NULL;
              current->next = NULL;
            }
        }
    }
  list->length--;
}

void *
ll_get_key (Linked_List *list, void *value)
{
  Node *current = list->head;

  while (current->next != NULL)
    {
      if (compare_key (current->value, value) == 0)
        return current->value;
      current = current->next;
    }
  return NULL;
}

/* Free the whole linked list */
void
ll_free_list (Linked_List *list)
{
  if (!list)
    {
      return;
    }
  if (list && !list->head)
    {
      free (list);
      return;
    }

  for (int len = list->length; len > 0; len--)
    {
      ll_delete (list, 0);
    }
  free (list);
}