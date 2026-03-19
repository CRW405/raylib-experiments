#include "raylib.h"
#include "stdio.h"

// run with gcc ... -lraylib 

int main(void) {
	// window setup
	const int screenWidth = 1080;
	const int screenHeight = 720;
	const int targetfps = 60;
	SetTargetFPS(targetfps);
	InitWindow(screenWidth, screenHeight, "Hello World");
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	// element setup
	Vector2 circlePosition = {0, (float)screenHeight/3};
	float circleSpeed = 100.0f;
	float circleRadius = 50.0f;

	// player setup
	Vector2 playerPos = {(float)screenWidth/2, (float)screenHeight/2};
	float playerSpeed = 10.0f;
	float playerRadius = 25.0f;

	// mouse setup
	Vector2 mousePos;
	float mouseRadius = 10.0f;
	int scrollSpeed = 5;

	// main loop
	while (!WindowShouldClose()) {
		circlePosition.x = (circlePosition.x > screenWidth) ? 0 : circlePosition.x + GetFrameTime() * circleSpeed;

		if(IsKeyDown(KEY_W)) playerPos.y -= playerSpeed;
		if(IsKeyDown(KEY_S)) playerPos.y += playerSpeed;
		if(IsKeyDown(KEY_A)) playerPos.x -= playerSpeed;
		if(IsKeyDown(KEY_D)) playerPos.x += playerSpeed;

		mousePos = GetMousePosition();
		mouseRadius += (float)(GetMouseWheelMove()*scrollSpeed);
		if (mouseRadius < 10.0f) mouseRadius = 10.0f;
		if (mouseRadius > 100.0f) mouseRadius = 100.0f;

		BeginDrawing();
			ClearBackground(WHITE);

			DrawText("Hi Space", 10, 10, 20, BLACK);
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 30, 20, BLACK);

			DrawCircleV(circlePosition, circleRadius, RED);
			DrawCircleV(playerPos, playerRadius, BLUE);
			DrawCircleV(mousePos, mouseRadius, GREEN);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
