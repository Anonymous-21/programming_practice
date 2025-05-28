#ifndef PLAYER_SELECTION_H
#define PLAYER_SELECTION_H

#include "constants.h"
#include "enums.h"

typedef struct MenuItem
{
	char* text;
	int font_size;
	int width;
	int x;
	int y;

} MenuItem;

extern char player_selection_items[NUM_PLAYER_SELECTION_ITEMS]
								  [PLAYER_SELECTION_STR_LEN];

typedef struct PlayerSelection
{
	MenuItem items[NUM_PLAYER_SELECTION_ITEMS];
	int selected;

} PlayerSelection;

void
player_selection_init(PlayerSelection* player_selection);
void
player_selection_draw(PlayerSelection* player_selection);
void
player_selection_update(PlayerSelection* player_selection,
						GameState* game_state);

#endif // PLAYER_SELECTION_H