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

  // fetch_data(LAST_30_DAYS);

  AppState state;
  init_satellite_positions(&state);
  init_state(&state, -1);

  state.time_scale = 1.0;
  Renderer renderer = renderer_create(SCREENWIDTH, SCREENHEIGHT);

  while (!WindowShouldClose()) {

    calc_positions(&state);

    // printf("Mouse available? %d\n", state.sat_trails);
    // if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    //   printf("CLICK!\n");
    // }
    // printf("mouse: %d %d\n", GetMouseX(), GetMouseY());

    renderer_render(&renderer, &state);
  }

  // cleanup

  renderer_destroy(&renderer);

  return 0;
}
