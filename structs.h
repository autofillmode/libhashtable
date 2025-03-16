#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum HT_TYPE
{
  STRING,
  INT,
  FLOAT
} HT_TYPE;

typedef struct Pair {
    void* Key;
    void* Value;
    int deleted;
} Pair;

typedef struct Node
{
  struct Pair *pair;
  struct Node *next;
  enum HT_TYPE key_type;
} Node;

typedef struct Linked_List 
{
  Node* head;
  Node* tail;
  int length;
} Linked_List;

typedef struct HashTable {
    int size;
    int collisions;
    int reallocs;
    int capacity;
    Linked_List** array;
} Hash_Table;

#endif