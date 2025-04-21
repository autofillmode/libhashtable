#include "../src/hashtable.h"
#include <stdio.h>

int
main (void)
{
  Hash_Table *ht = ht_init (STRING, FLOAT);

  float points = 3.14;
  float *np = &points;
  ht_put ("points", np, ht);

  printf ("points: %0.2f\n", *(float *)ht_get ("points", ht));

  ht_free (ht);
}
