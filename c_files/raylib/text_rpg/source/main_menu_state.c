#include "../include/main_menu_state.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void
main_menu_init(MainMenu* main_menu)
{
	main_menu->selected = 0;
	Rectangle source_rectangle =
	  (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() };
	int vertical_gap = 50;

	main_menu->items = malloc(main_menu_items_count * sizeof(MenuItem));
	if (main_menu->items == NULL) {
		fprintf(stderr, "Memory not allocated in main_menu->items\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < main_menu_items_count; i++) {

		main_menu->items[i].text = main_menu_items[i];
		main_menu->items[i].font_size = 40;
		main_menu->items[i].width =
		  MeasureText(main_menu->items[i].text, main_menu->items[i].font_size);
		main_menu->items[i].x = (int)source_rectangle.x +
								(int)source_rectangle.width / 2 -
								main_menu->items[i].width / 2;
		main_menu->items[i].y = (int)source_rectangle.y +
								(int)source_rectangle.height / 2 -
								main_menu->items[i].font_size / 2 +
								(i * vertical_gap) - vertical_gap / 2;
	}
}

void
main_menu_draw(MainMenu* main_menu)
{
	for (int i = 0; i < main_menu_items_count; i++) {
		Color color = (i == main_menu->selected) ? BLACK : GRAY;

		// draw menu item
		DrawText(main_menu->items[i].text,
				 main_menu->items[i].x,
				 main_menu->items[i].y,
				 main_menu->items[i].font_size,
				 color);

		// draw array selector
		if (i == main_menu->selected) {
			DrawText(">",
					 main_menu->items[i].x - 30,
					 main_menu->items[i].y,
					 40,
					 BLACK);
		}
	}
}

void
main_menu_update(MainMenu* main_menu, GameState* current_state)
{
	if (IsKeyPressed(KEY_DOWN)) {
		main_menu->selected = (main_menu->selected + 1) % main_menu_items_count;
	}
	if (IsKeyPressed(KEY_UP)) {
		main_menu->selected =
		  (main_menu->selected - 1 + main_menu_items_count) %
		  main_menu_items_count;
	}

	if (IsKeyPressed(KEY_ENTER) && *current_state == STATE_MAIN_MENU) {
		switch (main_menu->selected) {
			case 0:
				*current_state = STATE_PLAYER_SELECTION;
				break;
			case 1:
				*current_state = STATE_GAME_QUIT;
				break;
		}
	}
}

void
main_menu_free(MainMenu* main_menu)
{
	free(main_menu->items);
	main_menu->items = NULL;
}