#include "include/satellite.h"
#include "include/state.h"
#include <stdio.h>
#include <stdlib.h>
#define SCREENWIDTH 800
#define SCREENHEIGHT 800

int main() {

  // create app state

  AppState state;

  Satellite *satellites =
      get_satellites_from_file("../data/fetched.txt", &state.sat_count);

  double r[3], v[3];

  for (int i = 0; i < state.sat_count; i++) {
    getRV(&(satellites[i].tle), 0.0, r, v);

    printf("\nSatellite: %s\n", satellites[i].name);
    printf("Position (km): [%.6f, %.6f, %.6f]\n", r[0], r[1], r[2]);
    printf("Velocity (km/s): [%.6f, %.6f, %.6f]\n", v[0], v[1], v[2]);
  }

  // fetch data process data
  // start up rendering
  // render loop
  // cleanup

  for (int i = 0; i < state.sat_count; i++) {
    free(&satellites[i]);
  }

  return 0;
}
