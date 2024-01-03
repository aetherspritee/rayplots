#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

// blank space at window edges in pixels
#define BORDER 20
#define INTERNAL_MAX_HEIGHT 20.0
#define INTERNAL_MAX_WIDTH 20.0
#define INTERNAL_MIN_HEIGHT -20.0
#define INTERNAL_MIN_WIDTH -20.0

// i need axes
// i need to place the axes on the window
// i need to place points on the window in a way that respects the axes
// i need to integrate the borders

// FIXME: current test case doesnt work
Vector2 GetOrigin(int max_x, int min_x, int max_y, int min_y) {
  Vector2 origin;
  if (min_x < 0 && max_x < 0) {
    // x axis from very right to left
    origin.x = GetScreenWidth() - BORDER;
  } else if (min_x > 0) {
    // x axis from middle to left and right
    origin.x = BORDER;
  } else {
    // x axis from left to right
    origin.x = GetScreenWidth() / 2;
  }

  if (min_y < 0 && max_y < 0) {
    // y axis from very top to bottom
    origin.y = BORDER;
  } else if (min_y > 0) {
    // y axis from middle to top and bottom
    origin.y = GetScreenHeight() - BORDER;
  } else {
    // y axis from very bottom to top
    origin.y = GetScreenHeight() / 2;
  }
  return origin;
}

Vector2 CoordinateTransform(Vector2 origin, Vector2 data) {
  // transform the data such that it is relative to the given origin
  Vector2 transformed_data = {origin.x + data.x, origin.y - data.y};
  return transformed_data;
}

void DrawPoints(Vector2 *data, Vector2 origin, Color color, int marker_size) {
  for (int i = 0; i < sizeof(&data); i++) {
    DrawCircleV(CoordinateTransform(origin, data[i]), marker_size, color);
  }
}

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
