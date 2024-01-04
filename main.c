#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdio.h>

// blank space at window edges in pixels
#define BORDER_OUTLINE_X1 10
#define BORDER_OUTLINE_X2 10
#define BORDER_OUTLINE_Y1 40
#define BORDER_OUTLINE_Y2 10
#define INTERNAL_MAX_HEIGHT 20.0
#define INTERNAL_MAX_WIDTH 20.0
#define INTERNAL_MIN_HEIGHT -20.0
#define INTERNAL_MIN_WIDTH -20.0
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

const int BORDER_X1 = 10 + BORDER_OUTLINE_X1;
const int BORDER_Y1 = 10 + BORDER_OUTLINE_Y1;
const int BORDER_X2 = 10 + BORDER_OUTLINE_X2;
const int BORDER_Y2 = 10 + BORDER_OUTLINE_Y2;

// the plan:
// 1. 2d scatter plots
// 2. 3d scatter plots
// 3. axes (2d/3d) and border outline
// 4. line plots
// 5. surface plots
// 6. bring opacity into the equation
// 7. render images onto plots
// 8. multiple things in one plot (2 images)
// 9. multiple plots in a single window

// FIXME: current test case doesnt work
Vector2 GetOrigin(Vector2 min, Vector2 max) {
  Vector2 origin;
  if (min.x < 0 && max.x <= 0) {
    // x axis from very right to left
    origin.x = GetScreenWidth() - BORDER_X2;
  } else if (min.x > 0) {
    // x axis from left to right
    origin.x = BORDER_X1;
  } else {
    // x axis from middle to left and right
    origin.x = (GetScreenWidth() - BORDER_X1 - BORDER_X2) / 2 + BORDER_X1;
  }

  if (min.y < 0 && max.y <= 0) {
    // y axis from very top to bottom
    origin.y = BORDER_Y1;
  } else if (min.y > 0) {
    // y axis from middle to top and bottom
    origin.y = GetScreenHeight() - BORDER_Y2;
  } else {
    // y axis from very bottom to top
    origin.y = (GetScreenHeight() - BORDER_Y1 - BORDER_Y2) / 2 + BORDER_Y1;
  }
  return origin;
}

void DrawBorder(Color color) {
  DrawLine(BORDER_OUTLINE_X1, GetScreenHeight() - BORDER_OUTLINE_Y2,
           BORDER_OUTLINE_X1, BORDER_OUTLINE_Y1, color);
  DrawLine(BORDER_OUTLINE_X1, BORDER_OUTLINE_Y1,
           GetScreenWidth() - BORDER_OUTLINE_X2, BORDER_OUTLINE_Y1, color);
  DrawLine(GetScreenWidth() - BORDER_OUTLINE_X2,
           GetScreenHeight() - BORDER_OUTLINE_Y2,
           GetScreenWidth() - BORDER_OUTLINE_X2, BORDER_OUTLINE_Y1, color);
  DrawLine(BORDER_OUTLINE_X1, GetScreenHeight() - BORDER_OUTLINE_Y2,
           GetScreenWidth() - BORDER_OUTLINE_X2,
           GetScreenHeight() - BORDER_OUTLINE_Y2, color);
}

Vector2 CoordinateTransform(Vector2 origin, Vector2 data, Vector2 *max) {
  // transform the data such that it is relative to the given origin
  // TODO: make sure points are normalized, therefore always shown within the
  // max.x = od_x1 bzw od_x2
  // max.y = od_y1 bzw od_y2
  int OD_x1 = origin.x - BORDER_X1;
  int OD_x2 = GetScreenWidth() - BORDER_X2 - origin.x;
  int OD_y1 = origin.y - BORDER_Y1;
  int OD_y2 = GetScreenHeight() - BORDER_Y2 - origin.y;
  data.y = (data.y / max->y) * MAX(OD_y1, OD_y2);
  data.x = (data.x / max->x) * MAX(OD_x1, OD_x2);
  Vector2 transformed_data = {origin.x + data.x, origin.y - data.y};

  return transformed_data;
}

Vector2 GetDataMin(Vector2 data[], unsigned long size) {
  Vector2 min = {INFINITY, INFINITY};
  for (unsigned long i = 0; i < size; i++) {
    if (data[i].x < min.x) {
      min.x = data[i].x;
    }
    if (data[i].y < min.y) {
      min.y = data[i].y;
    }
  }
  return min;
}

Vector2 GetDataMax(Vector2 *data, unsigned long size) {
  Vector2 max = {-INFINITY, -INFINITY};
  for (unsigned long i = 0; i < size; i++) {
    if (data[i].x > max.x) {
      max.x = data[i].x;
    }
    if (data[i].y > max.y) {
      max.y = data[i].y;
    }
  }
  return max;
}

void DrawPoints(Vector2 *data, Vector2 origin, Color color, int marker_size,
                Vector2 *max, unsigned long size_of_data) {
  for (int i = 0; i < size_of_data; i++) {
    if (fabs(data[i].x) > max->x) {
      max->x = fabs(data[i].x);
    }

    if (fabs(data[i].y) > max->y) {
      max->y = fabs(data[i].y);
    }
    DrawCircleV(CoordinateTransform(origin, data[i], max), marker_size, color);
  }
}

// additional behaviour i want:
// - axes
// - place points on the window in a way that respects the axes
// - buttons with functionality
// - zoom
// - panning (3d atleast)

int main(void) {
  Vector2 MaximumValues = {-INFINITY, -INFINITY};
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 224, "rayplot");

  while (!WindowShouldClose()) {
    BeginDrawing();
    Color gruvbox_background = GetColor(0x282828AA);
    ClearBackground(gruvbox_background);
    DrawBorder(RAYWHITE);
    Vector2 test_data[] = {{-20, -40},  {-40, -20}, {-60, -10}, {-80, -20},
                           {-100, -40}, {0, 0},     {-50, -50}, {100, 100},
                           {100, -100}, {-30, -30}, {-30, 40}};
    unsigned long data_size = sizeof(test_data) / sizeof(test_data[0]);

    Vector2 origin = GetOrigin(GetDataMin(test_data, data_size),
                               GetDataMax(test_data, data_size));
    DrawCircleV(origin, 3, RAYWHITE);

    DrawPoints(test_data, origin, RED, 2, &MaximumValues, data_size);

    Vector2 test_data2[] = {
        {-200, -400}, {-400, -200}, {-600, -100}, {-80, -200}};
    unsigned long data_size2 = sizeof(test_data2) / sizeof(test_data2[0]);

    DrawPoints(test_data2, origin, RED, 2, &MaximumValues, data_size2);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
