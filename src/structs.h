#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum HT_TYPE { STRING, INT, FLOAT, ANY } HT_TYPE;

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
  HT_TYPE key_type;
  HT_TYPE value_type;
} Hash_Table;

#endif