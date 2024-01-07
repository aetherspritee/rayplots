#include "raylib.h"
#include "raymath.h"
#include "rayplots_2d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int size = 1;
Vector2 *data;
int data_elements = 0;

// the plan:
// 1. 2d scatter plots [DONE]
//    - automatically scaling points to fill the whole screen
//    - automatically place origin to use space most efficiently
//    - TODO: update points and origin every time new points are added
// 2. Write functions to automatically handle everything
// 2. axes (2d/3d), all points should respect it
//    - TODO: make axis merge with borders
//    - TODO: place numbers smarter
// 3. 3d scatter plots
// 4. line plots
// 5. surface plots
// 6. bring opacity into the equation
// 7. render images onto plots
// 8. multiple things in one plot (2 images)
// 9. multiple plots in a single window
// 10. menu buttons
// 11. zooming and panning

// possible extras:
// - do extens not just based on maximum, but also minimum (if small negative
//   number and large positive number, just show bit of negative side of cs)
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

void DrawHandler(Vector2 new_data, Vector2 *data[]) {
  // keeps track of all added points
  // re-calculates origin based on new points
  // redraws coordinate system
  // adds new points
}

// FIXME: this needs to track a plot or smth
int CreatePlot(Vector2 new_data[], int data_length) {
  // i want this to automatically create the array that tracks all data
  // such that you only pass new data to it
  size = data_elements + data_length;
  data = realloc(data, size * sizeof(Vector2));
  if (data == NULL) {
    printf("Array not allocated!");
    return 1;
  }

  int el_copy = data_elements;
  int curr_data_elements = 0;
  for (int i = el_copy; i < el_copy + data_length; i++) {
    /* printf("%i\n", i - data_length); */
    data[i].x = new_data[curr_data_elements].x;
    data[i].y = new_data[curr_data_elements].y;
    curr_data_elements += 1;
  }
  data_elements += curr_data_elements;

  // recalculate min/max
  // recalculate origin
  // redraw coordinate system
  // add all points into plot

  return 0;
}

int main(void) {
  data = calloc(size, sizeof(Vector2));
  if (data == NULL) {
    printf("Array not allocated!");
    return 1;
  }
  Vector2 MaximumValues = {-INFINITY, -INFINITY};
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 224, "rayplot");

  Vector2 data_down_left[] = {{-20, -40}, {-40, -20},  {-60, -10},
                              {-80, -20}, {-100, -40}, {0, 0},
                              {-50, -50}, {-30, -30},  {-30, -40}};

  unsigned long data_size = sizeof(data_down_left) / sizeof(data_down_left[0]);

  CreatePlot(data_down_left, data_size);

  Vector2 test_up_both[] = {{-200, 400}, {-400, 200}, {600, 100}, {80, 200}};
  unsigned long data_size2 = sizeof(test_up_both) / sizeof(test_up_both[0]);

  CreatePlot(test_up_both, data_size2);

  while (!WindowShouldClose()) {
    BeginDrawing();
    Color gruvbox_background = GetColor(0x282828AA);
    ClearBackground(gruvbox_background);
    DrawBorder(RAYWHITE);

    Vector2 origin = GetOrigin(GetDataMin(data_down_left, data_size),
                               GetDataMax(data_down_left, data_size));
    DrawCoordinateSystem(origin, MaximumValues);
    /* DrawCircleV(origin, 3, RAYWHITE); */

    DrawPoints2D(data_down_left, origin, RED, 2, &MaximumValues, data_size);

    Vector2 test_up_both[] = {{-200, 400}, {-400, 200}, {600, 100}, {80, 200}};
    unsigned long data_size2 = sizeof(test_up_both) / sizeof(test_up_both[0]);

    DrawPoints2D(test_up_both, origin, RED, 2, &MaximumValues, data_size2);

    EndDrawing();
  }

  CloseWindow();

  free(data);
  return 0;
}
