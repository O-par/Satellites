#include "include/renderer.h"
#include "include/satellite.h"
#include "include/state.h"
#include "include/util.h"
#include <raylib.h>

Renderer renderer_create(int width, int height) {
  Renderer r = {.screen_width = width,
                .screen_height = height,
                .camera = {.position = (Vector3){100.0f, 100.0f, 100.0f},
                           .target = (Vector3){0.0f, 0.0f, 0.0f},
                           .up = (Vector3){0.0f, 1.0f, 0.0f},
                           .fovy = 45.0f,
                           .projection = CAMERA_PERSPECTIVE}};

  InitWindow(r.screen_width, r.screen_height, "TESTING");
  SetTargetFPS(60);

  return r;
}

void renderer_render(Renderer *r, AppState *state) {
  UpdateCamera(&r->camera, CAMERA_ORBITAL);

  if (IsKeyPressed(KEY_Z)) {
    r->camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  }

  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(r->camera);
  DrawFPS(GetScreenWidth() - 100, 10);
  for (int i = 0; i < state->sat_count; i++) {
    Vector3 pos = state->satellites[i].position_ECI;
    DrawCube(pos, 0.5f, 0.5f, 0.5f, GREEN);
  }

  EndMode3D();
  DrawFPS(GetScreenWidth() - 100, 10);
  DrawText("Free camera default controls:", 20, 20, 10, RAYWHITE);
  DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
  DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
  DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);
  char txt[100];
  snprintf(txt, sizeof(txt), "Number of satellites being rendered: %d",
           state->sat_count);
  DrawText(txt, 20, 100, 15, RAYWHITE);
  for (int i = 0; i < state->sat_count; i++) {
    Vector3 pos = state->satellites[i].position_ECI;
    Vector2 text_pos =
        GetWorldToScreen((Vector3){pos.x, pos.y + 2.5f, pos.z}, r->camera);
    DrawText(state->satellites[i].name, text_pos.x, text_pos.y, 8, GREEN);
  }

  EndDrawing();
}

void renderer_destroy(Renderer *r) { CloseWindow(); }
