#include "include/satellite.h"
#include "include/TLE.h"
#include "include/util.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L1_LEN 128
#define L2_LEN 128
#define NAME_LEN 128

Satellite create_sat_from_tle(char *name, char *line1, char *line2) {
  TLE tle;

  parseLines(&tle, line1, line2);

  Satellite sat = {.tle = tle, .epoch = tle.epoch, .trail_count = 0};
  strncpy(sat.objectID, tle.objectID, sizeof(sat.objectID));

  trim_trailing_spaces(name);
  strncpy(sat.name, name, sizeof(sat.name));
  sat.name[sizeof(sat.name) - 1] = '\0';
  return sat;
};

Satellite *get_satellites_from_file(char *filepath, int *s_count) {
  int line_count = count_lines(filepath);

  if (line_count % 3 != 0) {
    fprintf(stderr,
            "[Error] Line count in file '%s' not divisible by 3 (%d lines)\n",
            filepath, line_count);
    return NULL;
  }

  int sat_count = line_count / 3;
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    fprintf(stderr, "[Error] Failed to open file '%s'\n", filepath);
    return NULL;
  }

  Satellite *sats = malloc(sat_count * sizeof(Satellite));
  if (!sats) {
    fprintf(stderr, "[Error] Memory allocation failed for %d satellites\n",
            sat_count);
    fclose(fp);
    return NULL;
  }

  char name[NAME_LEN];
  char tle1[L1_LEN];
  char tle2[L2_LEN];

  int i = 0;
  while (i < sat_count && fgets(name, NAME_LEN, fp) != NULL &&
         fgets(tle1, L1_LEN, fp) != NULL && fgets(tle2, L2_LEN, fp) != NULL) {
    // Strip trailing newlines
    name[strcspn(name, "\n")] = '\0';
    tle1[strcspn(tle1, "\n")] = '\0';
    tle2[strcspn(tle2, "\n")] = '\0';

    /*
    // Validation
    if (line1[0] != '1' || line2[0] != '2') {
      fprintf(stderr, "[Warning] Skipping malformed TLE at index %d\n", i);
      continue;
    }
    */
    Satellite t_sat = create_sat_from_tle(name, tle1, tle2);

    printf("\nName: %s", t_sat.name);
    sats[i++] = t_sat;
  }

  fclose(fp);

  if (i == 0) {
    fprintf(stderr, "[Error] No valid satellites parsed from file '%s'\n",
            filepath);
    free(sats);
    return NULL;
  }
  *s_count = i;
  return sats;
}
