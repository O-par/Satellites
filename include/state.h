#pragma once

#include "fetch.h"

#include "satellite.h"
#include <stdbool.h>
#include <time.h>
typedef struct AppState {
  Satellite *satellites;
  int sat_count;
  double time_scale;
  bool sat_trails;
  bool app_running;
  double start_time_ms;
  bool fetch;
} AppState;

void init_state(AppState *state);
