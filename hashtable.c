#include "hashtable.h"
#include "compare.h"
#include "llist.h"
#include "murmur.h"
#include "structs.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void hash_and_add (HT_Node *, Linked_List **, int, Hash_Table *);
static HT_Node *ht_get_node (Node *);

Hash_Table *
ht_init ()
{
  Hash_Table *ht = calloc (1, sizeof (Hash_Table));
  if (!ht)
    {
      perror ("ht_init: failed to allocate memory for hash table.");
      exit (EXIT_FAILURE);
    }
  ht->array = calloc (DEFAULT_SIZE, sizeof (Linked_List));
  if (!ht->array)
    {
      perror ("ht_init: failed to allocate memory for internal array!");
      exit (EXIT_FAILURE);
    }
  ht->size = 0;
  ht->collisions = 0;
  ht->capacity = (int)(DEFAULT_SIZE * LOAD_FACTOR);
  return ht;
}

/* return null if not found */
void *
ht_get (void *key, Hash_Table *ht)
{
  uint32_t hash = murmur3_32 (key, strlen (key), 0);
  int index = (hash & 0x7fffffff) % ht->capacity;

  if (ht->array[index] == NULL)
    {
      return NULL;
    }

  Node *current = ht->array[index]->head;

  if (compare_key (current->value, key) == 0)
    {
      return ht_get_node (current)->pair->Value;
    }

  if (compare_key (ht_get_node (current)->pair->Key, key) != 0)
    {
      return ll_get_key (ht->array[index], key);
    }
  return NULL;
}

void
ht_put (void *key, void *value, Hash_Table *ht)
{

  if (ht->size == ht->capacity)
    {
      ht_reallocate (ht);
    }

  HT_Node *newNode = calloc (1, sizeof (HT_Node));

  if (!newNode)
    {
      perror ("ht_add: failed to allocate memory for new Node!");
      exit (EXIT_FAILURE);
    }

  newNode->key_type = infer_type (key);
  newNode->pair = malloc (sizeof (Pair));

  if (newNode->key_type == STRING)
    {
      newNode->pair->Key = strdup (key);
    }
  else
    {
      newNode->pair->Key = key;
    }
  if (infer_type (value) == STRING)
    {
      newNode->pair->Value = strdup (value);
    }
  else
    {
      newNode->pair->Value = value;
    }

  hash_and_add (newNode, ht->array, ht->capacity, ht);

  ht->size++;
}

void
ht_reallocate (Hash_Table *ht)
{
  int newCapacity = ht->capacity * 2;
  Linked_List **newArr = calloc (ht->capacity, sizeof (Linked_List));
  if (!newArr)
    {
      perror ("ht_reallocate: failed to allocate memory for new array!");
    }

  for (int i = 0; i < ht->capacity; i++)
    {
      if (ht->array[i] != NULL)
        {
          Node *current = ht->array[i]->head;

          do
            {
              /* FIXME: this alloc isn't free'd!!*/
              HT_Node *newNode = calloc (1, sizeof (HT_Node));

              if (!newNode)
                {
                  perror ("ht_add: failed to allocate memory for new Node!");
                  exit (EXIT_FAILURE);
                }
              newNode->pair = calloc (1, sizeof (Pair));

              newNode->key_type
                  = infer_type (ht_get_node (current)->pair->Key);
              newNode->pair = malloc (sizeof (Pair));

              if (newNode->key_type == STRING)
                {
                  newNode->pair->Key
                      = strdup (ht_get_node (current)->pair->Key);
                }
              else
                {
                  newNode->pair->Key = ht_get_node (current)->pair->Key;
                }
              if (infer_type (ht_get_node (current)->pair->Value) == STRING)
                {
                  newNode->pair->Value
                      = strdup (ht_get_node (current)->pair->Value);
                }
              else
                {
                  newNode->pair->Value = ht_get_node (current)->pair->Value;
                }
              hash_and_add (newNode, newArr, newCapacity, ht);

              current = current->next;
            }
          while (current != NULL);
          ll_free_list (ht->array[i]);
        }
    }

  free (ht->array);
  ht->capacity = newCapacity;
  ht->array = newArr;
  ht->reallocs++;
}

static void
hash_and_add (HT_Node *src, Linked_List **dst, int capacity, Hash_Table *ht)
{
  uint32_t hash = murmur3_32 (src->pair->Key, strlen (src->pair->Key), 0);
  int index = (hash & 0x7fffffff) % capacity;

  if (dst[index] == NULL)
    {
      dst[index] = ll_init ();
      ll_push_front (dst[index], src);
    }
  else
    {
      /* Update a Value */
      if (compare_key (dst[index]->head->value, src->pair->Key)
          == 0) /* if the keys match... */
        {
          ht_get_node (dst[index]->head)->pair->Value
              = strdup (src->pair->Value);
          free (src->pair);
          free (src);
          return;
        }
      ht->collisions++;
      ll_push_back (dst[index], src);
    }
}

static HT_Node *
ht_get_node (Node *node)
{
  return node->value;
}

void
ht_print (Hash_Table *ht)
{
  for (int i = 0; i < ht->capacity; i++)
    {
      if (ht->array[i] != NULL)
        {
          ll_print (ht->array[i]);
          printf ("\n");
        }
    }
}

void
ht_free (Hash_Table *ht)
{
  for (int i = 0; i <= ht->capacity; i++)
    {
      if (ht->array[i] != NULL)
        {
          ll_free_list (ht->array[i]);
        }
    }
  free (ht->array);
  free (ht);
}
