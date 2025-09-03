#include "constants.h"
#include "renderer.h"
#include "satellite.h"
#include "state.h"
#include <raylib.h>
#include <stdio.h>

int main() {

  // create app state

  // fetch data process data
  // start up rendering
  // render loop

  AppState state;
  init_satellite_positions(&state);
  init_state(&state, -1);

  Renderer renderer = renderer_create(SCREENWIDTH, SCREENHEIGHT);
  // DisableCursor();

  while (!WindowShouldClose()) {

    calc_positions(&state);

    GUI_render(&renderer, &state);

    renderer_render(&renderer, &state);
  }

  // cleanup

  renderer_destroy(&renderer);

  return 0;
}
