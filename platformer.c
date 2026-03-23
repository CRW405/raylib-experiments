#include "raylib.h"
#include <math.h>

#define GRAVITY 400
#define PLAYER_HOR_SPEED 350.0f
#define PLAYER_JUMP_SPEED 350.0f
#define JUMP_LIMIT 2
#define DASH_LIMIT 2

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

// module declaration
void UpdatePlayer(Player *player, EnvRect *envRects, int envRectLength, float deltaTime);

int main(void)
{
	// window setup
	int s_width = 1080;
	int s_height = 720;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(s_width, s_height, "Platformer");
	SetTargetFPS(60);

	// player setup
	Player player = { 0 };
	player.pos = (Vector2){ 0, 0 };
	player.jump_count = JUMP_LIMIT;
	player.dash_count = DASH_LIMIT;
	player.color = GOLD;

	// enviroment setup
	EnvRect envRects[] = {
		{{100, 100, s_width-200, s_height-200}, 0, BLUE},
		{{0, s_height/2, s_width, 100}, 1, GRAY},
		{{s_width/3, 200, s_width/3, 50}, 1, LIGHTGRAY}
	};
	int envRectLength = sizeof(envRects)/sizeof(envRects[0]);

	// camera setup
	Camera2D cam = { 0 };
	Vector2 camPos = {-s_width/2, s_height/2};
	cam.target = camPos;
	cam.zoom = 1.0f;

	// game loop
	while (!WindowShouldClose()) {
		// frame setup
		ClearBackground(RAYWHITE);
		float deltaTime = GetFrameTime();
		
		// controls
		cam.zoom = expf(logf(cam.zoom) + ((float)GetMouseWheelMove()*0.1f));
		UpdatePlayer(&player, envRects, envRectLength, deltaTime); // processes controls and valid operations

		BeginDrawing();
		BeginMode2D(cam);

			for (int i = 0; i < envRectLength; i++) {
				DrawRectangleRec(envRects[i].rect, envRects[i].color);
			}

			Rectangle playerRect = {player.pos.x, player.pos.y-40.0f, 40.0f, 40.0f};
			DrawRectangleRec(playerRect, player.color);

			camPos = (Vector2){player.pos.x - s_width/2, player.pos.y -  s_height/2};
			cam.target = camPos;

		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void UpdatePlayer(Player *player, EnvRect *envRects, int envRectLength, float deltaTime) {
	// controls
	if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE)) && player->jump_count > 0) {
		player->cur_speed = -PLAYER_JUMP_SPEED;
		player->jump_count--;
	}
	if (IsKeyDown(KEY_A)) player->pos.x -= PLAYER_HOR_SPEED * deltaTime;
	// if (IsKeyDown(KEY_S)) player->pos.y += PLAYER_HOR_SPEED * deltaTime;
	if (IsKeyDown(KEY_D)) player->pos.x += PLAYER_HOR_SPEED * deltaTime;
	// TODO: dash
	if (IsKeyDown(KEY_R)) {
		player->pos.x = 0;
		player->pos.y = 0;
	}

	// apply vertical movement and gravity
	player->pos.y += player->cur_speed * deltaTime;
	player->cur_speed += GRAVITY * deltaTime;

	// player rectangle for collision
	Rectangle pRect = { player->pos.x, player->pos.y - 40.0f, 40.0f, 40.0f };

	for (int i = 0; i < envRectLength; i ++) {
		EnvRect *rect = envRects + i;
		if (!rect->collision) continue;
		if (CheckCollisionRecs(pRect, rect->rect)) {
			// compute overlap
			float left = fmaxf(pRect.x, rect->rect.x);
			float right = fminf(pRect.x + pRect.width, rect->rect.x + rect->rect.width);
			float top = fmaxf(pRect.y, rect->rect.y);
			float bottom = fminf(pRect.y + pRect.height, rect->rect.y + rect->rect.height);
			float overlapX = right - left;
			float overlapY = bottom - top;

			if (overlapX < overlapY) {
				// resolve horizontally
				float pCenterX = pRect.x + pRect.width * 0.5f;
				float rCenterX = rect->rect.x + rect->rect.width * 0.5f;
				if (pCenterX < rCenterX) {
					player->pos.x -= overlapX;
				} else {
					player->pos.x += overlapX;
				}
				pRect.x = player->pos.x;
			} else {
				// resolve vertically
				float pCenterY = pRect.y + pRect.height * 0.5f;
				float rCenterY = rect->rect.y + rect->rect.height * 0.5f;
				if (pCenterY < rCenterY) {
					// landed on top
					player->pos.y = rect->rect.y; // bottom aligns with env top
					player->cur_speed = 0.0f;
					player->jump_count = JUMP_LIMIT;
				} else {
					// hit head on bottom of platform
					player->pos.y = rect->rect.y + rect->rect.height + pRect.height;
					player->cur_speed = 0.0f;
				}
				pRect.y = player->pos.y - pRect.height;
			}
		}
	}
}

