#include "state.h"
#include "util.h"

void init_state(AppState *state) {
  state->time_scale = 50.0;
  state->start_time_ms = current_millis();
  state->fetch = false;

  if (state->fetch) {

    fetch_data(ACTIVE);
  }
}
