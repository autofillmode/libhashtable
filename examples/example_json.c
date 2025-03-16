#include "hashtable.h"
#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* THIS NEEDS cJSON TO BE INSTALLED! */


void read_from_file (const char *);

int
main (int argc, char *argv[])
{
  read_from_file (argv[1]);

  return 0;
}

void
read_from_file (const char *filename)
{
  Hash_Table *ht = ht_init ();
  FILE *fp = fopen (filename, "r");
  if (!fp)
    {
      printf ("File %s not found!\n", filename);
      exit (EXIT_FAILURE);
    }

  size_t linesiz = 0;
  char *linebuf = NULL;
  ssize_t linelen = 0;
  int lines = 0;

  cJSON *json;
  cJSON *json_id;
  cJSON *json_fname;

  clock_t begin_read = clock ();
  while ((linelen = getline (&linebuf, &linesiz, fp)) > 0)
    {
      json = cJSON_Parse (linebuf);
      if (!json)
        {
          printf ("Error! Failed parsing json from line %d \n", lines);
        }
      else
        {
          json_id = cJSON_GetObjectItem (json, "id");
          json_fname = cJSON_GetObjectItem (json, "firstName");
          if (json_id && json_fname)
            {
              ht_put (json_id->valuestring, json_fname->valuestring, ht);
            }
        }
      cJSON_Delete (json);
      lines++;
    }

  clock_t end_read = clock ();

  free (linebuf);

  fclose (fp);

  double time_reading
      = (double)(end_read - begin_read) / CLOCKS_PER_SEC * 1000;

  printf ("Reading and adding coders' names and IDs from file %s to the "
          "hashtable took %lf ms.\n",
          filename, time_reading);

  printf ("%d collisions, %d reallocs, %d elements.\n", ht->collisions,
          ht->reallocs, ht->size);

  ht_free (ht);
}
