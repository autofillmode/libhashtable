#include "llist.h"
#include "compare.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Add a node to the head of the linked list. */
void
ll_push_front (Linked_List *list, void *val)
{
  HT_Node *new = malloc (sizeof (HT_Node));
  if (!new)
    {
      perror ("ll_add_: couldn't alloc memory for new node!");
      exit (EXIT_FAILURE);
    }
  new = val;

  new->next = list->head;
  list->head = new;

  if (list->length == 0)
    {
      list->tail = list->head;
    }

  list->length++;
}

/* Add a Node to the tail of the linked list. If list is empty, calls
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

  HT_Node *current = list->tail;
  HT_Node *new = malloc (sizeof (HT_Node));
  if (!new)
    {
      perror ("ll_add_to_end: couldn't alloc memory for new node!");
      exit (EXIT_FAILURE);
    }

  new = val;

  current->next = new;
  list->tail = current->next;

  current->next->next = NULL;

  list->length++;
}

/* Initializes a new linked list */
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
ll_get_key (const Linked_List *list, HT_TYPE key_type, void *key)
{
  HT_Node *current = list->head;

  for (int i = 0; i < list->length; i++)
    {
      if (!compare_key (current, key_type, key)) /* key is found*/
        return current->pair->Value;
      current = current->next;
    }
  return NULL;
}

/* Print the whole linked list. If need be, pass a callback as print_with. */
void
ll_print (const Linked_List *list, char *(*print_with) (void *))
{
  if (!list || list->length == 0 || !list->head)
    {
      return;
    }
  HT_Node *current = list->head;
  int len = list->length;

  do
    {
      if (print_with)
        {
          char *member = print_with (current);
          printf ("[%s]->", member);
          free (member);
        }
      else
        printf ("[Node %p]->", current);
      current = current->next;
    }
  while (--len);
  printf ("(null)");
}

/* Delete a single item at index from the list.  If the index contains a heap
 * alloc'd value, pass a callback as free_with. If not, pass NULL as free_with.
 */
void
ll_delete (Linked_List *list, const int index, void (*free_with) (void *))
{

  HT_Node *to_delete;

  if (index == 0)
    {
      to_delete = list->head;
      list->head = list->head->next;

      if (list->head == NULL)
        list->tail = NULL;
    }
  else
    {
      HT_Node *current = list->head;
      for (int i = 0; i < index - 1; i++)
        {
          current = current->next;
        }
      to_delete = current->next;
      current->next = current->next->next;

      if (to_delete == list->tail)
        list->tail = current;
    }

  if (free_with)
    {
      free_with (to_delete);
    }

  list->length--;
}

/* Free the whole linked list. If the list contains heap alloc'd values, pass a
 * callback as free_with(). If there are only stack-allocs pass NULL.
 */
void
ll_free_list (Linked_List *list, void (*free_with) (void *))
{
  if (!list)
    {
      return;
    }

  HT_Node *current = list->head;
  while (current != NULL)
    {
      HT_Node *next = current->next;
      if (free_with)
        {
          free_with (current);
        }
      current = next;
    }
  free (list);
}