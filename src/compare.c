#include "compare.h"
#include "structs.h"
#include <ctype.h>
#include <string.h>

int
compare_key (HT_Node *node, HT_TYPE key_type, void *value)
{
  switch (key_type)
    {
    case ANY: /* compare pointers if object is any */
      return (node->pair->Key == value);
    case STRING:
      return strcmp (node->pair->Key, value);
    case INT:
      if (*(int *)node->pair->Key < *(int *)value)
        return -1;
      if (*(int *)node->pair->Key > *(int *)value)
        return 1;
      else
        return 0;
    case FLOAT:
      if (*(float *)node->pair->Key < *(float *)value)
        return -1;
      if (*(float *)node->pair->Key > *(float *)value)
        return 1;
      else
        return 0;
    default:
      return 1;
    }
}