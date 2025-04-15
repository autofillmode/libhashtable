#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum HT_TYPE { STRING, INT, FLOAT } HT_TYPE;

typedef struct Pair {
  void *Key;
  void *Value;
  int deleted;
} Pair;

typedef struct HT_Node {
  struct Pair *pair;
  struct HT_Node *next;
  enum HT_TYPE key_type;
} HT_Node;

typedef struct HashTable {
  int size;
  int collisions;
  int reallocs;
  int capacity;
  struct Linked_List **array;
} Hash_Table;

#endif