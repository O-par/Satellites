#pragma once
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

double get_minutes_since_epoch(long epoch_ms);

long current_millis();

void trim_trailing_spaces(char *str);

int count_lines(const char *filepath);
