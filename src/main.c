#include "include/fetch.h"
#include "include/renderer.h"
#include "include/satellite.h"
#include "include/state.h"
#include <bits/time.h>
#include <raylib.h>
#include <stdio.h>
#include <time.h>
#define SCREENWIDTH 800
#define SCREENHEIGHT 800

// FIXME refactor this later
long current_millis() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return (long)(ts.tv_sec * 1000L + ts.tv_nsec / 1000000L);
}

int main() {

  // create app state

  // fetch_data(ACTIVE);

  AppState state;

  Satellite *satellites =
      get_satellites_from_file("data/fetched.txt", &state.sat_count);

  long now = current_millis();

  state.satellites = satellites;
  double r[3], v[3];
  for (int i = 0; i < state.sat_count; i++) {
    double min_after_epoch = (now - satellites[i].tle.epoch) / 60000.0;
    getRV(&(satellites[i].tle), min_after_epoch, r, v);

    satellites[i].position_ECI = (Vector3){r[0] / 200, r[2] / 200, -r[1] / 200};

    printf("\nSatellite: %s\n", satellites[i].name);
    printf("Position (km): [%.6f, %.6f, %.6f]\n", r[0], r[1], r[2]);
    printf("Velocity (km/s): [%.6f, %.6f, %.6f]\n", v[0], v[1], v[2]);
  }

  // fetch data process data
  // start up rendering
  // render loop

  Renderer renderer = renderer_create(1920, 1080);

  while (!WindowShouldClose()) {
    renderer_render(&renderer, &state);
  }

  // cleanup

  renderer_destroy(&renderer);

  return 0;
}
