#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "game_data.h"
#include "menu_item.h"

typedef struct MainMenu
{
	MenuItem* items;
	int selected;

} MainMenu;

void
main_menu_init(MainMenu* main_menu);
void
main_menu_draw(MainMenu* main_menu);
void
main_menu_update(MainMenu* main_menu, GameState *current_state);
void
main_menu_free(MainMenu* main_menu);

#endif // MAIN_MENU_STATE_H