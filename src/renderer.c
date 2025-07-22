#include "renderer.h"
#include "satellite.h"
#include "state.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

#define EARTH_SCALE 0.06f
#define APP_TITLE "Satellite Propagator"

Renderer renderer_create(int width, int height) {
  Renderer r = {.screen_width = width,
                .screen_height = height,
                .camera = {.position = (Vector3){100.0f, 100.0f, 100.0f},
                           .target = (Vector3){0.0f, 0.0f, 0.0f},
                           .up = (Vector3){0.0f, 1.0f, 0.0f},
                           .fovy = 80.0f,
                           .projection = CAMERA_PERSPECTIVE}};

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
  DrawText("Free camera default controls:", 20, 20, 20, RAYWHITE);
  DrawText("- Mouse Wheel to Zoom in-out", 40, 50, 20, DARKGRAY);
  DrawText("- Mouse Wheel Pressed to Pan", 40, 70, 20, DARKGRAY);
  DrawText("- Z to zoom to (0, 0, 0)", 40, 90, 20, DARKGRAY);
  char txt[100];
  snprintf(txt, sizeof(txt), "Number of satellites being rendered: %d",
           state->sat_count);
  DrawText(txt, 20, 120, 25, RAYWHITE);
  for (int i = 0; i < state->sat_count; i++) {
    Vector3 pos = state->satellites[i].position_ECI;
    Vector2 text_pos =
        GetWorldToScreen((Vector3){pos.x, pos.y + 2.5f, pos.z}, r->camera);
    DrawText(state->satellites[i].name, text_pos.x, text_pos.y, 8, GREEN);
  }

  EndDrawing();
}

void renderer_destroy(Renderer *r) {
  UnloadModel(r->earth);
  CloseWindow();
}
