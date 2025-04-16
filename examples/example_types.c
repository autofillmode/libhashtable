#include "../src/hashtable.h"
#include <stdio.h>

int
main (void)
{
  Hash_Table *ht = ht_init ();

  float points = 3.14;
  float *np = &points;
  ht_put ("points", np, ht);

  int levels = 42;
  int *lp = &levels;
  ht_put ("levels", lp, ht);

  ht_put ("username", "jabberwocky", ht);

  printf ("points: %0.2f\n", *(float *)ht_get ("points", ht));
  printf ("levels: %d\n", *(int *)ht_get ("levels", ht));
  printf ("username: %s\n", (char *)ht_get ("username", ht));

  int bottles_of_beer = 99;
  int *bottlep = &bottles_of_beer;
  ht_put (bottlep, "bottles of beer", ht);

  ht_put ("key", "lock", ht);

  printf ("We have exactly 99 %s.\n", (char *)ht_get (bottlep, ht));
  printf ("The key opens the %s.\n", (char *)ht_get ("key", ht));

  ht_free (ht);
}
