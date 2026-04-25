//
// Raylib 2D mapping engine
//

// Features:
// Modal Editing
// Map loading/saving
// Different Shapes (Rectangles, Circles, Triangles, Polygons)
// Color Support
// Texture support
// Snap to grid

// MVP:
// Modal Editing (selecting, moving, resizing, deleting)
// Map loading/saving
// Different Shapes (Rectangles, Circles)
// Color Support

// NOTES:
//

// TODO:
//

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// window setup
	int s_width = 1080;
	int s_height = 720;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(s_width, s_height, "Mapper");
	SetTargetFPS(60);

	// camera setup
	Camera2D cam = {0};
	Vector2 camPos = {0, 0};
	cam.zoom = 1.0f;

	// main loop
	while (!WindowShouldClose()) {
		// controls
		// cam movement
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / cam.zoom);
			cam.target = Vector2Add(cam.target, delta);
		}
		// TODO: Arrow key, WASD, Vi movement

		// zoom
		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);
			cam.offset = GetMousePosition();
			cam.target = mouseWorldPos;
			float scale = wheel;
			cam.zoom = Clamp(expf(logf(cam.zoom) + (scale / 5)), 0.1f, 100.0f);
		}
		// TODO: Right click drag zoom
		// TODO: CTRL -/+ zoom, CTRL Up Down, CTRL JK zoom

		// render
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(cam);

		// draw grid
		// TODO: make grid infinite
		rlPushMatrix();
		rlTranslatef(0, 25 * 50, 0);
		rlRotatef(90, 1, 0, 0);
		DrawGrid(500, 10);
		rlPopMatrix();
		EndMode2D();

		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);
		DrawTextEx(GetFontDefault(),
		           TextFormat("%.0f, %.0f", mouseWorldPos.x, mouseWorldPos.y),
		           Vector2Add(GetMousePosition(), (Vector2){-44, -24}), 20, 2,
		           BLACK);

		EndDrawing();
	}
	CloseWindow();
	return EXIT_SUCCESS;
}
