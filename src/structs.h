#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Pair {
  void *Key;
  void *Value;
} Pair;

typedef struct HT_Node {
  struct Pair *pair;
  struct HT_Node *next;
} HT_Node;

typedef struct HashTable {
  int size;
  int collisions;
  int reallocs;
  int capacity;
  struct Linked_List **array;
} Hash_Table;

#endif