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

double get_minutes_since_epoch(long epoch_ms) {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  long now = ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
  return (now - epoch_ms) / 60000.0;
}

int main() {

  // create app state

  fetch_data(ACTIVE);

  AppState state;

  Satellite *satellites =
      get_satellites_from_file("data/fetched.txt", &state.sat_count);

  long now = current_millis();

  state.satellites = satellites;
  double r[3], v[3];
  for (int i = 0; i < state.sat_count / 9; i++) {
    double min_after_epoch = (now - satellites[i].tle.epoch) / 60000.0;
    getRV(&(satellites[i].tle), min_after_epoch, r, v);

    satellites[i].position_ECI =
        (Vector3){(r[0] / 200), (r[2] / 200), (-r[1] / 200)};

    printf("\nSatellite: %s\n", satellites[i].name);
    printf("Position (km): [%.3f, %.3f, %.3f]\n", r[0], r[1], r[2]);
    printf("Velocity (km/s): [%.3f, %.3f, %.3f]\n", v[0], v[1], v[2]);
  }

  // fetch data process data
  // start up rendering
  // render loop

  Renderer renderer = renderer_create(1920, 1080);
  DisableCursor();
  double time_scale = 100.0;
  double start_time_ms = current_millis();
  while (!WindowShouldClose()) {
    long now_ms = current_millis();
    double elapsed_minutes = (now_ms - start_time_ms) / 60000.0;
    double scaled_time = elapsed_minutes * time_scale;

    for (int i = 0; i < state.sat_count; i++) {
      double epoch_minutes =
          (start_time_ms - state.satellites[i].tle.epoch) / 60000.0;
      double minutes_since_epoch = scaled_time + epoch_minutes;

      double r[3], v[3];
      getRV(&state.satellites[i].tle, minutes_since_epoch, r, v);

      state.satellites[i].position_ECI = (Vector3){
          (float)(r[0] / 200), (float)(r[2] / 200), (float)(-r[1] / 200)};
    }

    renderer_render(&renderer, &state);
  }

  // cleanup

  renderer_destroy(&renderer);

  return 0;
}
