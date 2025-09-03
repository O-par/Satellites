#include "state.h"
#include "util.h"

void init_state(AppState *state, enum SAT_SETS set) {
  state->time_scale = 50.0;
  state->start_time_ms = current_millis();
  state->fetch = false;
  state->sat_names = false;

  if (state->fetch && set != -1) {

    fetch_data(set);
  }
}
