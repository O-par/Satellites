#include "include/SGP4.h"
#include "include/TLE.h"
#include "include/renderer.h"
#include <raylib.h>
#include <stdio.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 800

int main() {

  InitWindow(SCREENWIDTH, SCREENHEIGHT,
             "raylib [core] example - 3d camera free");

  Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

  Camera3D camera = {0};
  camera.position = (Vector3){15.0f, 15.0f, 15.0f}; // Camera position
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  DisableCursor(); // Limit cursor to relative movement inside the window

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    UpdateCamera(&camera, CAMERA_ORBITAL);

    if (IsKeyPressed('Z'))
      camera.target = (Vector3){0.0f, 0.0f, 0.0f};

    BeginDrawing();

    // XXX Draw

    ClearBackground(BLACK);

    BeginMode3D(camera);

    DrawGrid(60, 1.0f);

    DrawSphereWires(cubePosition, 4, 20, 20, GREEN);

    // XXX Stop drawing

    EndMode3D();

    DrawText("Free camera default controls:", 20, 20, 10, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
    DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
    DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
  return 0;
}
