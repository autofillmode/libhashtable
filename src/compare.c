#include "compare.h"
#include "structs.h"
#include <ctype.h>
#include <string.h>

int
compare_key (HT_Node *node, void *value)
{
  switch (node->key_type)
    {
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

static int
is_int (const char *key)
{
  if (*key == '-' || *key == '+') /* skip sign */
    {
      key++;
    }
  if (*key == '\0')
    return 0;

  while (*key)
    {
      if (!isdigit (*key))
        return 0;
      key++;
    }
  return 1;
}

static int
is_float (const char *key)
{
  int has_dot = 0;
  if (*key == '-' || *key == '+') /* skip sign */
    {
      key++;
    }
  if (*key == '\0') /* skip empty strings */
    return 0;

  while (*key)
    {
      if (*key == '.')
        {
          if (has_dot)
            return 0; /* can't have more than one dot! */
          has_dot = 1;
        }
      else if (!isdigit (*key)) /* only digits in floats! */
        {
          return 0;
        }
      key++;
    }
  return has_dot; /* has to have 1 dot to be a float */
}

HT_TYPE
infer_type (void *key)
{
  const char *key_string = (const char *)key;

  if (is_int (key_string))
    return INT;
  else if (is_float (key_string))
    return FLOAT;
  else
    return STRING;
}