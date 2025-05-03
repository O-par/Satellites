#include "../include/TLE.h"
#include <stdio.h>
#include <string.h>

int main() {
  char line1[] =
      "1 25544U 98067A   20029.54791435  .00000712  00000-0  21713-4 0  9993";
  char line2[] =
      "2 25544  51.6434  19.1283 0007415  64.0176  33.1317 15.49515321211603";

  char name[] = "testing";

  TLE tle;
  strncpy(tle.name, name, sizeof(name));
  strncpy(tle.line1, line1, 69);
  tle.line1[69] = '\0';
  strncpy(tle.line2, line2, 69);
  tle.line2[69] = '\0';

  parseLines(&tle, tle.line1, tle.line2); // fills tle.rec

  printf("Name: %s\n", tle.name);
  printf("Time (min)       X (km)       Y (km)       Z (km)     VX (km/s)   VY "
         "(km/s)   VZ (km/s)\n");

  // t : time since epoch (in minutes)
  // r : output array for position vector
  // v : output array for velocity vector

  for (double t = 0; t <= 60; t += 10) {
    double r[3], v[3];
    getRV(&tle, t, r, v); // wrapper for sgp4()
    printf("%10.0f  %10.3f  %10.3f  %10.3f  %9.5f  %9.5f  %9.5f\n", t, r[0],
           r[1], r[2], v[0], v[1], v[2]);
  }

  return 0;
}
