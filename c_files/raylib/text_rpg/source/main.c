#include <raylib.h>

#include "../include/game_data.h"
#include "../include/main_menu_state.h"
#include "../include/player_selection_state.h"
#include "../include/player.h"

int
main(void)
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;
    const char SCREEN_TITLE[] = "Text Rpg";
    const Color SCREEN_BACKGROUND = LIGHTGRAY;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

	bool game_quit = false;

	GameState current_state = STATE_MAIN_MENU;
	MainMenu main_menu;
	PlayerSelection player_selection;

	Player player;

    main_menu_init(&main_menu);
	player_selection_init(&player_selection);

	while (!WindowShouldClose()) {
		if (game_quit)
			break;

		BeginDrawing();
		ClearBackground(SCREEN_BACKGROUND);

		switch (current_state) {
			case STATE_MAIN_MENU:
				main_menu_draw(&main_menu);
				main_menu_update(&main_menu, &current_state);
				break;
			case STATE_PLAYER_SELECTION:
				player_selection_draw(&player_selection);
				player_selection_update(&player_selection, &current_state, &player);
				break;
			case STATE_TOWN:
				break;
			case STATE_GAME_QUIT:
				game_quit = true;
				break;
		}

		EndDrawing();
	}

	main_menu_free(&main_menu);
	player_selection_free(&player_selection);
	CloseWindow();

	return 0;
}