#include "../include/constants.h"
#include <raylib.h>

int
main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(SCREEN_BACKGROUND);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}