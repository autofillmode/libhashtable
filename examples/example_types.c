#include "../src/hashtable.h"
#include <stdio.h>

int
main (void)
{
  Hash_Table *ht = ht_init (STRING, ANY);

  float points = 3.14;
  float *np = &points;
  ht_put ("points", np, ht);

  int another = 774;
  int *ap = &another;
  ht_put ("another", ap, ht);

  printf ("points: %0.2f\n", *(float *)ht_get ("points", ht));
  printf ("another: %d\n", *(int *)ht_get ("another", ht));

  ht_free (ht);
}
