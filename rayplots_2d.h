#ifndef RAYPLOTS_2D_H_
#define RAYPLOTS_2D_H_

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

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

void DrawMarkerX(Vector2 position, int length) {
  Vector2 startPos, endPos;
  startPos.x = endPos.x = position.x;
  startPos.y = position.y - length / 2;
  endPos.y = position.y + length / 2;
  DrawLineV(startPos, endPos, RAYWHITE);
}

void DrawMarkerY(Vector2 position, int length) {
  Vector2 startPos, endPos;

  startPos.y = endPos.y = position.x;
  startPos.x = position.y - length / 2;
  endPos.x = position.y + length / 2;
  DrawLineV(startPos, endPos, RAYWHITE);
}

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

Vector2 CoordinateTransform(Vector2 origin, Vector2 data, Vector2 *max) {
  // transform the data such that it is relative to the given origin
  // also scales them to maximum value to make sure everything is visible
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

void DrawPoints2D(Vector2 *data, Vector2 origin, Color color, int marker_size,
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

void DrawCoordinateSystemMarkersX(Vector2 x_axis, Vector2 origin, Vector2 max) {
  // TODO: pass color
  Vector2 startPos, endPos;
  int NumOfValuesToDisplayX = 10;
  // do markers at ends of x axis
  int length = 10;
  DrawMarkerX(CLITERAL(Vector2){x_axis.x, origin.y}, length);
  DrawMarkerX(CLITERAL(Vector2){x_axis.y, origin.y}, length);

  // draw number markers
  // TODO: place numbers more symmetrically
  int step_size = max.x / (NumOfValuesToDisplayX / 2);
  for (int i = 0; i <= max.x; i += step_size) {
    Vector2 pos = CoordinateTransform(origin, CLITERAL(Vector2){i, 0}, &max);
    DrawMarkerX(CLITERAL(Vector2){pos.x, origin.y}, 2);
    // draw number
    DrawText(TextFormat("%d", i), pos.x, pos.y, 4, RAYWHITE);
  }

  for (int i = 0; i >= -max.x; i -= step_size) {
    Vector2 pos = CoordinateTransform(origin, CLITERAL(Vector2){i, 0}, &max);
    DrawMarkerX(CLITERAL(Vector2){pos.x, origin.y}, 2);
    // draw number
    DrawText(TextFormat("%d", i), pos.x, pos.y, 4, RAYWHITE);
  }
}

void DrawCoordinateSystemMarkersY(Vector2 y_axis, Vector2 origin, Vector2 max) {
  // TODO: pass color
  Vector2 startPos, endPos;
  int NumOfValuesToDisplayY = 10;
  int length = 10;
  // do markers at ends of y axis
  DrawCircleV(origin, 5, RAYWHITE);
  DrawMarkerY(CLITERAL(Vector2){y_axis.x, origin.x}, length);
  DrawMarkerY(CLITERAL(Vector2){y_axis.y, origin.x}, length);

  // draw number markers
  int step_size = max.y / (NumOfValuesToDisplayY / 2);
  for (int i = 0; i <= max.y; i += step_size) {
    Vector2 pos = CoordinateTransform(origin, CLITERAL(Vector2){0, i}, &max);
    DrawMarkerY(CLITERAL(Vector2){pos.y, origin.x}, 5);
    // draw number
    DrawText(TextFormat("%d", i), pos.x, pos.y, 4, RAYWHITE);
  }

  for (int i = 0; i >= -max.y; i -= step_size) {
    Vector2 pos = CoordinateTransform(origin, CLITERAL(Vector2){0, i}, &max);
    DrawMarkerY(CLITERAL(Vector2){pos.y, origin.x}, 5);
    // draw number
    DrawText(TextFormat("%d", i), pos.x, pos.y, 4, RAYWHITE);
  }
}

void DrawCoordinateSystem(Vector2 origin, Vector2 max) {
  // TODO: allow different colors
  // x axis
  Vector2 startPosX, endPosX;
  startPosX.x = origin.x;
  startPosX.y = origin.y;
  endPosX.y = origin.y;
  if (origin.x == BORDER_X1) {
    endPosX.x = GetScreenWidth() - BORDER_X2 + BORDER_OUTLINE_X2;
  } else if (origin.x == GetScreenWidth() - BORDER_X2) {
    endPosX.x = BORDER_X1 - BORDER_OUTLINE_X1;
  } else {
    startPosX.x = GetScreenWidth() - BORDER_X2 + BORDER_OUTLINE_X2;
    endPosX.x = BORDER_X1 - BORDER_OUTLINE_X1;
  }
  DrawLineV(startPosX, endPosX, RAYWHITE);
  DrawCoordinateSystemMarkersX(CLITERAL(Vector2){startPosX.x, endPosX.x},
                               origin, max);
  // y axis
  Vector2 startPos, endPos = {0, 0};
  endPos.x = origin.x;
  startPos.x = origin.x;
  startPos.y = origin.y;
  if (origin.y == BORDER_Y1) {
    endPos.y = GetScreenHeight() - BORDER_Y2 + BORDER_OUTLINE_Y2 / 2;
  } else if (origin.y == GetScreenHeight() - BORDER_Y2) {
    endPos.y = BORDER_Y1 - BORDER_OUTLINE_Y2 / 2;
  } else {
    endPos.y = GetScreenHeight() - BORDER_Y2 + BORDER_OUTLINE_Y2 / 2;
    startPos.y = BORDER_Y1 - BORDER_OUTLINE_Y2 / 2;
  }

  DrawLineV(startPos, endPos, RAYWHITE);
  DrawCoordinateSystemMarkersY(CLITERAL(Vector2){startPos.y, endPos.y}, origin,
                               max);
}

#endif // RAYPLOTS_2D_H_
