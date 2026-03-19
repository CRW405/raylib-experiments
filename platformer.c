#include "raylib.h"
#include <math.h>

#define PLAYER_HOR_SPEED 250.0f
#define PLAYER_JUMP_SPEED 500.0f

typedef struct Player {
	Vector2 pos;
	float cur_speed;
	int jump_count;
	int dash_count;
	Color color;
} Player;

typedef struct EnvRect {
	Rectangle rect;
	bool collision;
	Color color;
} EnvRect;

int main(void)
{
	// window setup
	int s_width = 500;
	int s_height = 500;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(s_width, s_height, "Platformer");
	SetTargetFPS(60);

	// player setup
	Player player = { 0 };
	player.pos = (Vector2){ s_width/2, s_height/2 };
	int jump_limit = 2;
	int dash_limit = 2;
	player.jump_count = jump_limit;
	player.dash_count = dash_limit;
	player.color = BLUE;

	// enviroment setup
	EnvRect envRects[] = {
		{{100, 100, s_width-100, s_height-100}, 0, BLUE},
		{{0, s_height/2, s_width, s_height/2}, 1, GRAY }
	};
	int envRectLength = sizeof(envRects)/sizeof(envRects[0]);

	// camera setup
	Camera2D cam = { 0 };
	cam.target = player.pos;
	cam.zoom = 1.0f;

	// game loop
	while (!WindowShouldClose()) {
		// frame setup
		ClearBackground(RAYWHITE);
		float deltaTime = GetFrameTime();
		
		// controls
		cam.zoom = expf(logf(cam.zoom) + ((float)GetMouseWheelMove()*0.1f));
		// UpdatePlayer(&player, envRects, envRectLength, deltaTime) // processes controls and valid operations


		BeginDrawing();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
