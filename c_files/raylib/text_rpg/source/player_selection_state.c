#include "../include/player_selection_state.h"
#include "../include/player.h"
#include "../include/utils.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void
player_selection_init(PlayerSelection* player_selection)
{
	player_selection->selected = 0;
	player_selection->items =
	  malloc(player_menu_items_count * sizeof(MenuItem));
	if (player_selection->items == NULL) {
		fprintf(stderr, "Memory not allocated to player_selection->items\n");
		exit(EXIT_FAILURE);
	}

	// player items will be centered around this rect
	Rectangle source_rect =
	  (Rectangle){ 0, 0, GetScreenWidth() / 2, GetScreenHeight() / 2 - 50 };
	// gap between player items
	int vertical_gap = 50;

	for (int i = 0; i < player_menu_items_count; i++) {
		player_selection->items[i].text = player_menu_items[i].type;
		player_selection->items[i].font_size = 30;
		player_selection->items[i].width =
		  MeasureText(player_selection->items[i].text,
					  player_selection->items[i].font_size);
		player_selection->items[i].x = (int)source_rect.x +
									   (int)source_rect.width / 2 -
									   player_selection->items[i].width / 2;
		player_selection->items[i].y =
		  (int)source_rect.y + (int)source_rect.height / 2 -
		  player_selection->items[i].font_size / 2 + (i * vertical_gap) -
		  vertical_gap;
	}
}

void
player_selection_draw(PlayerSelection* player_selection)
{
	// screen division line
	DrawLineEx((Vector2){ GetScreenWidth() * 0.5f, 0 },
			   (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() },
			   5.0f,
			   BLACK);

	for (int i = 0; i < player_menu_items_count; i++) {
		Color color = (i == player_selection->selected) ? BLACK : GRAY;

		// draw menu items
		DrawText(player_selection->items[i].text,
				 player_selection->items[i].x,
				 player_selection->items[i].y,
				 player_selection->items[i].font_size,
				 color);

		if (i == player_selection->selected) {
			// draw selection arrow
			DrawText(">",
					 player_selection->items[i].x - 30,
					 player_selection->items[i].y,
					 40,
					 BLACK);

			// draw menu item properties
			center_and_draw_text(
			  TextFormat("Health: %.2f", player_menu_items[i].health),
			  30,
			  (Rectangle){ GetScreenWidth() * 0.5f,
						   0,
						   GetScreenWidth() * 0.5f,
						   GetScreenHeight() - 100 },
			  BLACK);
			center_and_draw_text(
			  TextFormat("Damage: %.2f", player_menu_items[i].damage),
			  30,
			  (Rectangle){ GetScreenWidth() * 0.5f,
						   0,
						   GetScreenWidth() * 0.5f,
						   GetScreenHeight() },
			  BLACK);
			center_and_draw_text(
			  TextFormat("Defense: %.2f", player_menu_items[i].defense),
			  30,
			  (Rectangle){ GetScreenWidth() * 0.5f,
						   0,
						   GetScreenWidth() * 0.5f,
						   GetScreenHeight() + 100 },
			  BLACK);
		}
	}
}

void
player_selection_update(PlayerSelection* player_selection,
						GameState* current_state,
						Player* player)
{
	if (IsKeyPressed(KEY_DOWN)) {
		player_selection->selected =
		  (player_selection->selected + 1) % player_menu_items_count;
	}
	if (IsKeyPressed(KEY_UP)) {
		player_selection->selected =
		  (player_selection->selected - 1 + player_menu_items_count) %
		  player_menu_items_count;
	}

	if (IsKeyPressed(KEY_ENTER) && *current_state == STATE_PLAYER_SELECTION) {
		player_init(player, player_menu_items[player_selection->selected].type);
		*current_state = STATE_TOWN;
	}
}

void
player_selection_free(PlayerSelection* player_selection)
{
	free(player_selection->items);
	player_selection->items = NULL;
}