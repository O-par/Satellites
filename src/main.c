#include "fetch.h"
#include "renderer.h"
#include "satellite.h"
#include "state.h"
#include "util.h"
#include <raylib.h>
#define SCREENWIDTH 800
#define SCREENHEIGHT 800

int main() {

  // create app state

  // fetch_data(LAST_30_DAYS);

  AppState state;

  init_satellite_positions(&state);

  // fetch data process data
  // start up rendering
  // render loop

  Renderer renderer = renderer_create(1920, 1080);
  DisableCursor();
  double time_scale = -100.0;
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
