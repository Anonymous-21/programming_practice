#include "raylib.h"
#include <math.h>

#define screenWidth 800
#define screenHeight 600

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

// 2D map layout (1 = wall, 0 = empty space)
int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int
main()
{
	// Initialize the window
	InitWindow(screenWidth, screenHeight, "Raylib Raycaster");

	// Player position and direction
	float posX = 4.5f, posY = 4.5f;	 // Start in the center of the map
	float dirX = -1.0f, dirY = 0.0f; // Initial direction vector (looking left)
	float planeX = 0.0f,
		  planeY = 0.66f; // 2D camera plane perpendicular to direction

	SetTargetFPS(60); // Set frame rate

	// Game loop
	while (!WindowShouldClose()) {
		// Player movement
		float moveSpeed = 0.05f;
		float strafeX = dirY; // perpendicular
		float strafeY = -dirX;

		if (IsKeyDown(KEY_W)) {
			if (worldMap[(int)(posY + dirY * moveSpeed)]
						[(int)(posX + dirX * moveSpeed)] == 0) {
				posX += dirX * moveSpeed;
				posY += dirY * moveSpeed;
			}
		}
		if (IsKeyDown(KEY_S)) {
			if (worldMap[(int)(posY - dirY * moveSpeed)]
						[(int)(posX - dirX * moveSpeed)] == 0) {
				posX -= dirX * moveSpeed;
				posY -= dirY * moveSpeed;
			}
		}

		// Rotate left (A) or right (D)
		if (IsKeyDown(KEY_D)) {
			float oldDirX = dirX;
			dirX = dirX * cosf(-0.05f) - dirY * sinf(-0.05f);
			dirY = oldDirX * sinf(-0.05f) + dirY * cosf(-0.05f);
			float oldPlaneX = planeX;
			planeX = planeX * cosf(-0.05f) - planeY * sinf(-0.05f);
			planeY = oldPlaneX * sinf(-0.05f) + planeY * cosf(-0.05f);
		}
		if (IsKeyDown(KEY_A)) {
			float oldDirX = dirX;
			dirX = dirX * cosf(0.05f) - dirY * sinf(0.05f);
			dirY = oldDirX * sinf(0.05f) + dirY * cosf(0.05f);
			float oldPlaneX = planeX;
			planeX = planeX * cosf(0.05f) - planeY * sinf(0.05f);
			planeY = oldPlaneX * sinf(0.05f) + planeY * cosf(0.05f);
		}

		// Draw scene
		BeginDrawing();
		ClearBackground(BLACK);

		for (int x = 0; x < screenWidth; x++) {
			// Calculate ray position and direction
			float cameraX = 2 * x / (float)screenWidth - 1;
			float rayDirX = dirX + planeX * cameraX;
			float rayDirY = dirY + planeY * cameraX;

			// Map square the player is in
			int mapX = (int)posX;
			int mapY = (int)posY;

			// Length of ray from one x/y-side to next x/y-side
			float deltaDistX = (rayDirX == 0) ? 1e30 : fabsf(1 / rayDirX);
			float deltaDistY = (rayDirY == 0) ? 1e30 : fabsf(1 / rayDirY);
			float sideDistX, sideDistY;

			// Step direction (positive or negative x/y)
			int stepX, stepY;

			int hit = 0; // Wall hit flag
			int side;	 // Was a NS or EW wall hit?

			// Calculate step and initial sideDist
			if (rayDirX < 0) {
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			} else {
				stepX = 1;
				sideDistX = (mapX + 1.0f - posX) * deltaDistX;
			}

			if (rayDirY < 0) {
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			} else {
				stepY = 1;
				sideDistY = (mapY + 1.0f - posY) * deltaDistY;
			}

			// Perform DDA
			while (hit == 0) {
				if (sideDistX < sideDistY) {
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				} else {
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				// Check if ray has hit a wall
				if (worldMap[mapY][mapX] > 0)
					hit = 1;
			}

			// Calculate distance to wall
			float perpWallDist;
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			// Calculate height of line to draw
			int lineHeight = (int)(screenHeight / perpWallDist);

			// Calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + screenHeight / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + screenHeight / 2;
			if (drawEnd >= screenHeight)
				drawEnd = screenHeight - 1;

			// Choose wall color based on side
			Color color = (side == 1) ? DARKGRAY : GRAY;

			// Draw the vertical wall stripe
			DrawLine(x, drawStart, x, drawEnd, color);
		}

		EndDrawing();
	}

	// Cleanup
	CloseWindow();
	return 0;
}
