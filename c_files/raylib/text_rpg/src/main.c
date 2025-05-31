#include "../inc/game_data.h"
#include "../inc/scrollable_menu.h"
#include <raylib.h>

int
main(void)
{
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const char SCREEN_TITLE[] = "Dungeon Delve - Text Rpg";
	const Color SCREEN_BACKGROUND = RAYWHITE;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

	GameState current_state = STATE_MAIN_MENU;

	ScrollableMenu main_menu;
	ScrollableMenu player_selection_menu;

	scrollable_menu_init(
	  &main_menu,
	  40,
	  5,
	  20,
	  (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() });

	scrollable_menu_init(
	  &player_selection_menu,
	  40,
	  5,
	  20,
	  (Rectangle){ 0, 0, GetScreenWidth() / 2, GetScreenHeight() });

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SCREEN_BACKGROUND);

		if (current_state == STATE_MAIN_MENU) {
			scrollable_menu_draw(
			  &main_menu, main_menu_array, main_menu_array_size);
			scrollable_menu_update(&main_menu);
            if (IsKeyPressed(KEY_ENTER) && main_menu_array[main_menu.selected])
            {
                current_state = STATE_PLAYER_SELECTION;
            }
		}
        else if (current_state = STATE_PLAYER_SELECTION)
        {
            // scrollable_menu_draw(&player_selection_menu, )
            ;
        }

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
