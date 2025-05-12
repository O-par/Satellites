#pragma once

#include <raylib.h>
#include <stdio.h>

#include "state.h"

typedef struct {
  int screen_width;
  int screen_height;
  Camera3D camera;
} Renderer;

Renderer *renderer_create(int width, int height);

void renderer_render(Renderer *r);

void renderer_destroy(Renderer *r, AppState *state);

int renderer_should_close(Renderer *r);
