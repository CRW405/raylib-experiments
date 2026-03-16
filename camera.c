#include "raylib.h"
#include <math.h>

int main(void)
{
	// game setup
	const int sWidth = 1080;
	const int sHeight = 720;
	InitWindow(sWidth, sHeight, "Camera Example");
	SetTargetFPS(1000000);

	// player setup
	Rectangle player = {sWidth/2, sHeight/2, 20, 40};
	const float playerSpeed = 200.0f;

	// camera setup
	Camera2D cam = { 0 };
	cam.target = (Vector2){player.x, player.y};
	cam.offset = (Vector2){sWidth/2, sHeight/2};
	cam.rotation = 0.0f;
	cam.zoom = 1.0f;

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_W)) player.y -= playerSpeed * GetFrameTime();
		if (IsKeyDown(KEY_S)) player.y += playerSpeed * GetFrameTime();
		if (IsKeyDown(KEY_A)) player.x -= playerSpeed * GetFrameTime();
		if (IsKeyDown(KEY_D)) player.x += playerSpeed * GetFrameTime();

		cam.target =  (Vector2){player.x, player.y};
		// mouse zoom with log scaling / smoothing
		cam.zoom = expf(logf(cam.zoom) + ((float)GetMouseWheelMove()*0.1f));

		BeginDrawing();
			ClearBackground(RAYWHITE);
			
			BeginMode2D(cam);
				DrawRectangle(sWidth/2, sHeight/2, 1000, 1000, DARKGRAY);

				DrawRectangleRec(player, RED);
			EndMode2D();
		
		DrawRectangle(0, 0, 200, 40, BLACK);
		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
