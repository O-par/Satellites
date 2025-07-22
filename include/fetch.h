#pragma once

enum SAT_SETS {
  SPACE_STATIONS = 1,
  LAST_30_DAYS = 2,
  HUNDRED_BRIGHT = 3,
  ACTIVE = 4,
  NOAA = 5,
  STARLINK = 6,
  GPS = 7,
  MILITARY = 8,
  CUBE_SAT = 9,
  ALL = 10
};

void fetch_data(enum SAT_SETS set);
