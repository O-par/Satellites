#include "renderer.h"
#include "satellite.h"
#include "state.h"
#include <raylib.h>
#define SCREENWIDTH 800
#define SCREENHEIGHT 800

int main() {

  // create app state

  // fetch data process data
  // start up rendering
  // render loop

  fetch_data(ACTIVE);

  AppState state;
  init_satellite_positions(&state);
  init_state(&state);

  Renderer renderer = renderer_create(1920, 1080);
  DisableCursor();

  while (!WindowShouldClose()) {

    calc_positions(&state);

    renderer_render(&renderer, &state);
  }

  // cleanup

  renderer_destroy(&renderer);

  return 0;
}
