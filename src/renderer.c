#include "renderer.h"
#include "constants.h"
#include "satellite.h"
#include "state.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define EARTH_SCALE 0.06f
#define APP_TITLE "Satellite Propagator"

Renderer renderer_create(int width, int height) {
  Renderer r = {.screen_width = width,
                .screen_height = height,
                .camera = {.position = (Vector3){100.0f, 100.0f, 100.0f},
                           .target = (Vector3){0.0f, 0.0f, 0.0f},
                           .up = (Vector3){0.0f, 1.0f, 0.0f},
                           .fovy = 80.0f,
                           .projection = CAMERA_CUSTOM}};

  InitWindow(r.screen_width, r.screen_height, APP_TITLE);
  SetTargetFPS(60);

  r.earth = LoadModel("models/Earth_1_12756.glb");
  if (r.earth.meshCount == 0) {
    printf("Error loading model");
    exit(EXIT_FAILURE);
  }
  Matrix correction = MatrixRotateY(DEG2RAD * -90.0f); // Or Y depending on test
  r.earth.transform = MatrixMultiply(r.earth.transform, correction);
  return r;
}

void renderer_render(Renderer *r, AppState *state) {
  UpdateCamera(&r->camera, CAMERA_FREE);

  if (IsKeyPressed(KEY_Z)) {
    r->camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  }

  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(r->camera);

  for (int i = 0; i < state->sat_count; i++) {
    Vector3 pos = state->satellites[i].position_ECI;
    DrawCube(pos, 0.5f, 0.5f, 0.5f, GREEN);
  }

  // drawing the earth
  DrawModel(r->earth, (Vector3){0, 0, 0}, EARTH_SCALE, WHITE);

  EndMode3D();
  DrawFPS(GetScreenWidth() - 100, 10);
  DrawText("Free camera default controls:", 20, 30, 20, RAYWHITE);
  DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 20, DARKGRAY);
  DrawText("- Mouse Wheel Pressed to Pan", 40, 80, 20, DARKGRAY);
  DrawText("- Z to zoom to (0, 0, 0)", 40, 100, 20, DARKGRAY);
  DrawText("- E to activate GUI", 40, 120, 20, DARKGRAY);
  char txt[100];
  snprintf(txt, sizeof(txt), "Number of satellites being rendered: %d",
           state->sat_count);
  DrawText(txt, 20, 150, 23, RAYWHITE);

  if (state->sat_names) {
    for (int i = 0; i < state->sat_count; i++) {
      Vector3 pos = state->satellites[i].position_ECI;
      Vector2 text_pos =
          GetWorldToScreen((Vector3){pos.x, pos.y + 2.5f, pos.z}, r->camera);
      DrawText(state->satellites[i].name, text_pos.x, text_pos.y, 8, GREEN);
    }
  }

  EndDrawing();
}

void GUI_render(Renderer *r, AppState *state) {

  GuiCheckBox((Rectangle){SCREENWIDTH - 200, 100, 70, 70},
              "Draw Satellite Trails", &state->sat_names);
}

void renderer_destroy(Renderer *r) {
  UnloadModel(r->earth);
  CloseWindow();
}
