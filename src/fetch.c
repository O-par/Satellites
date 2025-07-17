#include "include/fetch.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>

char *URL_from_set(enum SAT_SETS set) {
  switch (set) {
  case SPACE_STATIONS:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=stations&FORMAT=tle";
  case LAST_30_DAYS:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=last-30-days&FORMAT=tle";
  case HUNDRED_BRIGHT:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=visual&FORMAT=tle";
  case ACTIVE:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=active&FORMAT=tle";
  case NOAA:
    return "https://celestrak.org/NORAD/elements/gp.php?GROUP=noaa&FORMAT=tle";
  case STARLINK:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=starlink&FORMAT=tle";
  case GPS:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=gps-ops&FORMAT=tle";
  case MILITARY:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=military&FORMAT=tle";
  case CUBE_SAT:
    return "https://celestrak.org/NORAD/elements/"
           "gp.php?GROUP=cubesat&FORMAT=tle";
  case ALL:
    return "ALL";
  default:
    return "UNKNOWN";
  }
}

void fetch_data(enum SAT_SETS set) {
  char *URL = URL_from_set(set);
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  // write to file in binary
  FILE *fp = fopen("data/fetched.txt", "wb");
  if (!fp) {
    exit(1);
    perror("Failed to open file for writing");
    return;
  }
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      printf("\ncurl failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }

  fclose(fp);
}
