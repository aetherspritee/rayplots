#include "raylib.h"
#include "raymath.h"
#include "rayplots_2d.h"
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

// the plan:
// 1. 2d scatter plots
//    - automatically scaling points to fill the whole screen
//    - automatically place origin to use space most efficiently
// 3. axes (2d/3d), all points should respect it
// 2. 3d scatter plots
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
    DrawCoordinateSystem(origin, MaximumValues);
    /* DrawCircleV(origin, 3, RAYWHITE); */

    DrawPoints2D(test_data, origin, RED, 2, &MaximumValues, data_size);

    Vector2 test_data2[] = {
        {-200, -400}, {-400, -200}, {-600, -100}, {-80, -200}};
    unsigned long data_size2 = sizeof(test_data2) / sizeof(test_data2[0]);

    DrawPoints2D(test_data2, origin, RED, 2, &MaximumValues, data_size2);

    int val = 10;
    Vector2 text_coords =
        CoordinateTransform(origin, CLITERAL(Vector2){50, 50}, &MaximumValues);
    DrawText(TextFormat("%d", val), text_coords.x, text_coords.y, 4, RAYWHITE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
