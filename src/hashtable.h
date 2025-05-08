#include "llist.h"
#include "murmur.h"
#include "structs.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define DEFAULT_SIZE 32
#define LOAD_FACTOR 0.60

Hash_Table *ht_init();
void *ht_get(char *key, Hash_Table *ht);
void ht_put(char *key, void *value, Hash_Table *ht);
void ht_ensure_capacity(int capacity, Hash_Table *ht);
void ht_reallocate(Hash_Table *ht);
void ht_free(Hash_Table *ht, void (*free_with)(void *pair));
void ht_print(Hash_Table *ht);

#endif