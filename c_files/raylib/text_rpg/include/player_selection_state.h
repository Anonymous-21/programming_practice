#ifndef PLAYER_SELECTION_STATE_H
#define PLAYER_SELECTION_STATE_H

#include "game_data.h"
#include "menu_item.h"

typedef struct Player Player;

typedef struct PlayerSelection
{
	MenuItem* items;
	int selected;

} PlayerSelection;

void
player_selection_init(PlayerSelection* player_selection);
void
player_selection_draw(PlayerSelection* player_selection);
void
player_selection_update(PlayerSelection* player_selection,
						GameState* current_state, Player *player);
void
player_selection_free(PlayerSelection* player_selection);

#endif // PLAYER_SELECTION_STATE_H