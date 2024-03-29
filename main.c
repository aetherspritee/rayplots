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


// the plan:
// 1. 2d scatter plots [DONE]
//    - automatically scaling points to fill the whole screen
//    - automatically place origin to use space most efficiently
//    - update points and origin every time new points are added
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

void DrawHandler(Vector2 new_data, Vector2 *data[]) {
  // keeps track of all added points
  // re-calculates origin based on new points
  // redraws coordinate system
  // adds new points
}


int main(void) {
  data = calloc(size, sizeof(Vector2));
  if (data == NULL) {
    printf("Array not allocated!");
    return 1;
  }
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(400, 224, "rayplot");

  Vector2 data_down_left[] = {{-20, -40}, {-40, -20},  {-60, -10},
                              {-80, -20}, {-100, -40}, {0, 0},
                              {-50, -50}, {-30, -30},  {-30, -40}};

  unsigned long data_size = sizeof(data_down_left) / sizeof(data_down_left[0]);

  UpdatePlot(data_down_left, data_size, true);

  Vector2 test_up_both[] = {{-200, 400}, {-400, 200}, {600, 100}, {80, 200}};
  /* Vector2 test_up_both[] = {{-60,-60}}; */
  unsigned long data_size2 = sizeof(test_up_both) / sizeof(test_up_both[0]);

  UpdatePlot(test_up_both, data_size2, true);

  BeginDrawing();
  Color gruvbox_background = GetColor(0x282828AA);
  /* ClearBackground(gruvbox_background); */
  /* DrawBorder(RAYWHITE); */

  /* Vector2 origin = GetOrigin(GetDataMin(data_down_left, data_size), */
  /*                             GetDataMax(data_down_left, data_size)); */
  /* DrawCoordinateSystem(origin, MaximumValues); */
  /* /\* DrawCircleV(origin, 3, RAYWHITE); *\/ */

  /* DrawPoints2D(data_down_left, origin, RED, 2, &MaximumValues, data_size); */

  while (!WindowShouldClose()) {

    UpdatePlot(test_up_both,data_size2, true);

    EndDrawing();
  }

  CloseWindow();

  printf("Done\n");

  free(data);
  return 0;
}
