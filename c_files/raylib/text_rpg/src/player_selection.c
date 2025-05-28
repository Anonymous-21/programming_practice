#include "../include/player_selection.h"
#include <raylib.h>

char player_selection_items[NUM_PLAYER_SELECTION_ITEMS]
						   [PLAYER_SELECTION_STR_LEN] = {
							   "Warrior", "Ranger",	 "Mage",	  "Cleric",
							   "Rogue",	  "Paladin", "Berserker", "Necromancer",
							   "Druid",	  "Monk",
						   };

void
player_selection_init(PlayerSelection* player_selection)
{
	player_selection->selected = 0;
	Rectangle source_rect =
	  (Rectangle){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };

	int vertical_gap = 50;

	for (int i = 0; i < NUM_PLAYER_SELECTION_ITEMS; i++) {
		player_selection->items[i].text = player_selection_items[i];
		player_selection->items[i].font_size = 40;
		player_selection->items[i].width =
		  MeasureText(player_selection->items[i].text,
					  player_selection->items[i].font_size);
		player_selection->items[i].x = (int)source_rect.x +
									   (int)source_rect.width / 2 -
									   player_selection->items[i].width / 2;
		player_selection->items[i].y =
		  (int)source_rect.y + (int)source_rect.height / 2 -
		  player_selection->items[i].font_size / 2 + (i * vertical_gap) -
		  vertical_gap / 2;
	}
}

void
player_selection_draw(PlayerSelection *player_selection)
{
	for (int i = 0; i < NUM_PLAYER_SELECTION_ITEMS; i++) {
		Color color = (i == player_selection->selected) ? BLACK : GRAY;

		DrawText(player_selection->items[i].text,
				 player_selection->items[i].x,
				 player_selection->items[i].y,
				 player_selection->items[i].font_size,
				 color);

		// draw selection cursor
		if (i == player_selection->selected) {
			DrawText(">",
					 player_selection->items[i].x - 30,
					 player_selection->items[i].y,
					 player_selection->items[i].font_size,
					 BLACK);
		}
	}
}

void
player_selection_update(PlayerSelection* player_selection, GameState *game_state)
{
	if (IsKeyPressed(KEY_UP)) {
		player_selection->selected -= 1;
		player_selection->selected += NUM_PLAYER_SELECTION_ITEMS;
		player_selection->selected %= NUM_PLAYER_SELECTION_ITEMS;
	}
	if (IsKeyPressed(KEY_DOWN)) {
		player_selection->selected += 1;
		player_selection->selected %= NUM_PLAYER_SELECTION_ITEMS;
	}

	if (IsKeyPressed(KEY_ENTER)) {
		if (player_selection->selected == 0) {
			;
		} else if (player_selection->selected == 1) {
			;
		}
	}
}