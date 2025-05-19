#include "include/util.h"

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
