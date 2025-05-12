#pragma once
#include "satellite.h"
#include <stdbool.h>

typedef struct {
  Satellite *satellites;
  int sat_count;
  bool sat_trails;
  bool app_running;
} AppState;
