#include "satellite.h"
#include "TLE.h"
#include "state.h"
#include "util.h"
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

void init_satellite_positions(AppState *state) {
  Satellite *satellites =
      get_satellites_from_file("data/fetched.txt", &state->sat_count);

  long now = current_millis();

  state->satellites = satellites;
  double r[3], v[3];
  for (int i = 0; i < state->sat_count / 9; i++) {
    double min_after_epoch = (now - satellites[i].tle.epoch) / 60000.0;
    getRV(&(satellites[i].tle), min_after_epoch, r, v);

    satellites[i].position_ECI =
        (Vector3){(r[0] / 200), (r[2] / 200), (-r[1] / 200)};

    printf("\nSatellite: %s\n", satellites[i].name);
    printf("Position (km): [%.3f, %.3f, %.3f]\n", r[0], r[1], r[2]);
    printf("Velocity (km/s): [%.3f, %.3f, %.3f]\n", v[0], v[1], v[2]);
  }
}
