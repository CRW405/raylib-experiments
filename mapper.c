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
// https://www.raylib.com/examples.html

#include "raylib.h"
#include <math.h>

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
	}

	return EXIT_SUCCESS;
}
