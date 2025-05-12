#include "include/util.h"

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
