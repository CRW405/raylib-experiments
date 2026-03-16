#include "raylib.h"

// wun with gcc ... -lraylib 

int main(void) {
  // window setup
  const int screenWidth = 500;
  const int screenHeight = 500;
  const int targetfps = 60;
  SetTargetFPS(targetfps);
  InitWindow(screenWidth, screenHeight, "Hello World");

  //element setup
  Vector2 circlePosition = {0, (float)screenHeight/3};
  float circleSpeed = 100.0f;
  float circleRadius = 50.0f;


  // main loop
  while (!WindowShouldClose()) {
    circlePosition.x = (circlePosition.x > screenWidth) ? 0 : circlePosition.x + GetFrameTime() * circleSpeed;

    BeginDrawing();
    ClearBackground(WHITE);

    DrawText("Hi Space", 10, 10, 20, BLACK);
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 30, 20, BLACK);
    DrawCircleV(circlePosition, circleRadius, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
  
}
