#include <raylib.h>
#include <stdio.h>

int
main(void)
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const char SCREEN_TITLE[] = "";
	const Color SCREEN_BACKGROUND = RAYWHITE;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

	char* text =
	  LoadFileText("/home/anonymous/Documents/dungen_delve_data.json");

	printf("%s\n", text);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SCREEN_BACKGROUND);
		EndDrawing();
	}

	UnloadFileText(text);
	CloseWindow();

	return 0;
}