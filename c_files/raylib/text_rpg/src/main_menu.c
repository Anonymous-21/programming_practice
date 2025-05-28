#include "../include/main_menu.h"
#include <raylib.h>

char main_menu_items[NUM_MAIN_MENU_ITEMS][MAIN_MENU_ITEMS_STR_LEN] = { "START",
																	   "QUIT" };

void
main_menu_init(MainMenu* main_menu)
{
	main_menu->selected = 0;
	Rectangle source_rect = (Rectangle){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	for (int i = 0; i < NUM_MAIN_MENU_ITEMS; i++) {
		main_menu->items[i].text = main_menu_items[i];
		main_menu->items[i].font_size = 40;
		main_menu->items[i].width =
		  MeasureText(main_menu->items[i].text, main_menu->items[i].font_size);
		main_menu->items[i].x = (int)source_rect.x +
								(int)source_rect.width / 2 -
								main_menu->items[i].width / 2;
		main_menu->items[i].y = (int)source_rect.y +
								(int)source_rect.height / 2 -
								main_menu->items[i].font_size / 2;
	}
}

void
main_menu_draw(MainMenu* main_menu)
{
	for (int i = 0; i < NUM_MAIN_MENU_ITEMS; i++) {
		Color color = (i == main_menu->selected) ? BLACK : GRAY;

		DrawText(main_menu->items[i].text,
				 main_menu->items[i].x,
				 main_menu->items[i].y,
				 main_menu->items[i].font_size,
				 color);

		// draw selection cursor
		if (i == main_menu->selected) {
			DrawText(">",
					 main_menu->items[i].x - 30,
					 main_menu->items[i].y,
					 main_menu->items[i].font_size,
					 BLACK);
		}
	}
}

void
main_menu_update(MainMenu* main_menu, GameState *game_state)
{
	if (IsKeyPressed(KEY_UP)) {
		main_menu->selected -= 1;
		main_menu->selected += NUM_MAIN_MENU_ITEMS;
		main_menu->selected %= NUM_MAIN_MENU_ITEMS;
	}
	if (IsKeyPressed(KEY_DOWN)) {
		main_menu->selected += 1;
		main_menu->selected %= NUM_MAIN_MENU_ITEMS;
	}

	if (IsKeyPressed(KEY_ENTER) && game_state == STATE_MAIN) {
		if (main_menu->selected == 0) {
			;
		} else if (main_menu->selected == 1) {
			;
		}
	}
}