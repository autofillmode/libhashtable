#include "llist.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Add a node to the head of the linked list. */
void
ll_push_front (Linked_List *list, HT_Node *val)
{

  val->next = list->head;
  list->head = val;

  if (list->length == 0)
    {
      list->tail = list->head;
    }

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

  do
    {
      if (!strcmp (current->pair->Key, key)) /* key is found*/
        return current->pair->Value;
      current = current->next;
    }
  while (current->next != NULL);
  return NULL;
}

/* Print the whole linked list. If need be, pass a callback as print_with. */
void
ll_print (const Linked_List *list, char *(*print_with) (void *))
{
  if (!list || !list->head)
    {
      return;
    }
  HT_Node *current = list->head;

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
  while (current != NULL);
  printf ("(null)");
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
          free (current->pair);
          free (current);
        }
      else
        {
          free (current->pair);
          free (current);
        }
      current = next;
    }
  free (list);
}