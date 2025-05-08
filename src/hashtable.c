#include "hashtable.h"
#include "llist.h"
#include "murmur.h"
#include "structs.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void hash_and_add (HT_Node *, Linked_List **, int, Hash_Table *);

Hash_Table *
ht_init ()
{
  Hash_Table *ht = malloc (sizeof (Hash_Table));
  if (!ht)
    {
      perror ("ht_init: failed to allocate memory for hash table.");
      exit (EXIT_FAILURE);
    }
  ht->array = calloc (DEFAULT_SIZE, sizeof (Linked_List *));
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
ht_get (char *key, Hash_Table *ht)
{
  uint32_t hash = murmur3_32 (key, strlen (key), 0);
  int index = (hash & 0x7fffffff) % ht->capacity;

  if (ht->array[index] == NULL)
    {
      return NULL;
    }

  HT_Node *current = ht->array[index]->head;

  if (strcmp (current->pair->Key, key) == 0)
    {
      return current->pair->Value;
    }
  else
    {
      return ll_get_key (ht->array[index], key);
    }
}

void
ht_put (char *key, void *value, Hash_Table *ht)
{

  if (ht->size == ht->capacity)
    {
      ht_reallocate (ht);
    }

  HT_Node *newNode = malloc (sizeof (HT_Node));

  if (!newNode)
    {
      perror ("ht_add: failed to allocate memory for new Node!");
      exit (EXIT_FAILURE);
    }

  newNode->pair = malloc (sizeof (Pair));

  newNode->pair->Key = key;
  newNode->pair->Value = value;

  hash_and_add (newNode, ht->array, ht->capacity, ht);

  ht->size++;
}

void
ht_reallocate (Hash_Table *ht)
{
  int newCapacity = ht->capacity * 2;
  Linked_List **newArr = calloc (newCapacity, sizeof (Linked_List *));
  if (!newArr)
    {
      perror ("ht_reallocate: failed to allocate memory for new array!");
    }

  for (int i = 0; i < ht->capacity; i++)
    {
      if (ht->array[i] != NULL)
        {
          HT_Node *current = ht->array[i]->head;

          do
            {
              HT_Node *newNode = malloc (sizeof (HT_Node));

              if (!newNode)
                {
                  perror ("ht_add: failed to allocate memory for new Node!");
                  exit (EXIT_FAILURE);
                }

              newNode->pair = calloc (1, sizeof (Pair));

              newNode->pair->Key = current->pair->Key;
              newNode->pair->Value = current->pair->Value;

              hash_and_add (newNode, newArr, newCapacity, ht);

              current = current->next;
            }
          while (current != NULL);
          ll_free_list (ht->array[i], NULL);
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
      HT_Node *current = dst[index]->head;
      while (current->next != NULL)
        {
          if (strcmp (current->pair->Key, src->pair->Key) == 0)
            {
              current->pair->Value = src->pair->Value;
              return;
            }
          current = current->next;
        }
      ht->collisions++;
      ll_push_front (dst[index], src);
    }
}

char *
print_with (void *node)
{
  HT_Node *to_print = (HT_Node *)node;

  int len = strlen (to_print->pair->Key) + strlen (to_print->pair->Value) + 6;

  char *ret = malloc (len + 1);
  snprintf (ret, len, "K:%s V:%s", (char *)to_print->pair->Key,
            (char *)to_print->pair->Value);

  return ret;
}

void
ht_print (Hash_Table *ht)
{
  for (int i = 0; i < ht->capacity; i++)
    {
      if (ht->array[i] != NULL)
        {
          ll_print (ht->array[i], print_with);
          printf ("\n");
        }
    }
}

void
ht_free (Hash_Table *ht, void (*free_with) (void *pair))
{
  for (int i = 0; i < ht->capacity; i++)
    {
      if (ht->array[i] != NULL)
        {
          ll_free_list (ht->array[i], free_with);
        }
    }
  free (ht->array);
  free (ht);
}
