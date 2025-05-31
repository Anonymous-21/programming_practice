#include "../include/game_data.h"
#include "../include/menu.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 800;
	const char SCREEN_TITLE[] = "Dungeon Delve - Text Rpg";
	const Color SCREEN_BACKGROUND = LIGHTGRAY;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

	GameState current_state = STATE_MAIN_MENU;

	Menu main_menu;
	Menu player_selection_menu;

	Rectangle layout_rect_main_menu =
	  (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() };
	Rectangle layout_rect_player_selection_menu =
	  (Rectangle){ 0, 0, GetScreenWidth() / 2, GetScreenHeight() / 2 - 100 };

	const char* player_selection_menu_items[hero_array_size];
	for (int i = 0; i < hero_array_size; i++) {
		player_selection_menu_items[i] = hero_array[i].type;
	}

	menu_init(&main_menu,
			  main_menu_items,
			  main_menu_item_size,
			  40,
			  5,
			  20,
			  layout_rect_main_menu);
	menu_init(&player_selection_menu,
			  player_selection_menu_items,
			  hero_array_size,
			  40,
			  5,
			  20,
			  layout_rect_player_selection_menu);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SCREEN_BACKGROUND);

		if (current_state == STATE_MAIN_MENU) {
			menu_draw(&main_menu);
			menu_update(&main_menu);
			if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
				if (main_menu.selected == 0) {
					current_state = STATE_PLAYER_TYPE_SELECTION;
				} else if (main_menu.selected == 1) {
					break;
				}
			}
		} else if (current_state == STATE_PLAYER_TYPE_SELECTION) {
			menu_draw(&player_selection_menu);
			menu_update(&player_selection_menu);
		}

		EndDrawing();
	}

	menu_free(&main_menu);
	menu_free(&player_selection_menu);

	CloseWindow();

	return 0;
}