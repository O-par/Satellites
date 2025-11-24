#pragma once

#include "fetch.h"

#include "satellite.h"
#include <stdbool.h>
#include <time.h>
typedef struct AppState {
  Satellite *satellites;
  int sat_count;
  double time_scale;
  double start_time_ms;
  bool gui_active;
  bool sat_names;
  bool sat_trails;
  bool app_running;
  bool fetch;
} AppState;

void init_state(AppState *state, enum SAT_SETS set);
