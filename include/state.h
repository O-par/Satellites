#pragma once

#include "satellite.h"
#include <stdbool.h>

typedef struct AppState {
  Satellite *satellites;
  int sat_count;
  double time_scale;
  bool sat_trails;
  bool app_running;
} AppState;
