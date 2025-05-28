#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "constants.h"
#include "enums.h"
#include <raylib.h>

typedef struct MenuItem
{
	char* text;
	int font_size;
	int width;
	int x;
	int y;

} MenuItem;

extern char main_menu_items[NUM_MAIN_MENU_ITEMS][MAIN_MENU_ITEMS_STR_LEN];

typedef struct MainMenu
{
	MenuItem items[NUM_MAIN_MENU_ITEMS];
	int selected;

} MainMenu;

void
main_menu_init(MainMenu* main_menu);
void
main_menu_draw(MainMenu* main_menu);
void
main_menu_update(MainMenu* main_menu, GameState* game_state);

#endif // MAIN_MENU_H