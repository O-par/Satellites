#pragma once
#include "SGP4.h"
#include "TLE.h"
#include <raylib.h>

typedef struct {
  TLE tle;
  Vector3 position_ECI;
  int trail_count; // number of points in trail_points
  Vector3 trail_points[512];
  char name[64];
  char objectID[6];
  long epoch;

} Satellite;

// TODO
Satellite create_sat_from_tle(char *name, char *line1, char *line2);
Satellite *get_satellites_from_file(char *filepath, int *sat_count);
void delete_sat(Satellite *sat);
