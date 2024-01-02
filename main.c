#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 224, "rayplot");

  while (!WindowShouldClose()) {
    BeginDrawing();
    Color gruvbox_background = GetColor(0x282828AA);
    ClearBackground(gruvbox_background);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
