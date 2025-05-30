#include <raylib.h>

#define SIZE 10

void
center_and_draw_array(char* arr[],
					  int font_size,
					  int line_gap,
					  Rectangle rect,
					  int selected)
{
	int total_text_height = SIZE * font_size;
	int start_y = rect.y + (rect.height - total_text_height) / 2;

	for (int i = 0; i < SIZE; i++) {
		int text_width = MeasureText(arr[i], font_size);
		int text_x = (int)rect.x + (int)rect.width / 2 - text_width / 2;
		int text_y = start_y + i * (font_size + line_gap);

		Color color = (i == selected) ? BLACK : GRAY;

		DrawText(arr[i], text_x, text_y, font_size, color);

		if (i == selected) {
			DrawText(">", text_x - 30, text_y - 5, 40, BLACK);
		}
	}
}

int
main(void)
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const char SCREEN_TITLE[] = "Auto centering test";
	const Color SCREEN_BACKGROUND = LIGHTGRAY;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

	Rectangle rect = (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() };
	char* arr[SIZE] = { "TEST1", "TEST2", "TEST3", "TEST4", "TEST5",
						"TEST6", "TEST7", "TEST8", "TEST9", "TEST10" };
	int font_size = 30;
	int selected = 0;
	int line_gap = 5;
	int line_height = font_size + line_gap;
	int max_visible = rect.height / line_height;
	int scroll_offset = 0;

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_DOWN)) {
			selected = (selected + 1) % SIZE;
		}
		if (IsKeyPressed(KEY_UP)) {
			selected = (selected - 1 + SIZE) % SIZE;
		}

		BeginDrawing();
		ClearBackground(SCREEN_BACKGROUND);

		center_and_draw_array(arr, font_size, line_gap, rect, selected);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}