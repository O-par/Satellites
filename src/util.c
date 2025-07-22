#include "util.h"

double get_minutes_since_epoch(long epoch_ms) {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  long now = ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
  return (now - epoch_ms) / 60000.0;
}

long current_millis() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return (long)(ts.tv_sec * 1000L + ts.tv_nsec / 1000000L);
}

void trim_trailing_spaces(char *str) {
  size_t len = strlen(str);
  while (len > 0 && isspace((unsigned char)str[len - 1])) {
    str[--len] = '\0';
  }
}

int count_lines(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file)
    return -1; // Error opening file

  int lines = 0;
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n')
      lines++;
  }

  fclose(file);
  return lines;
}
