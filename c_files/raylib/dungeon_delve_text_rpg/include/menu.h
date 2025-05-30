#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef struct MenuItem
{
	const char* title;
	int font_size;
	int width;
	int x;
	int y;

} MenuItem;

typedef struct Menu
{
	MenuItem* items;
    int item_size;
	int selected;
	int vertical_gap;
    Rectangle layout_rect;

} Menu;

void
menu_init(Menu* menu, const char* item_arr[], int item_size, int font_size, Rectangle layout_rect);
void
menu_draw(Menu* menu);
void
menu_update(Menu* menu);
void
menu_free(Menu* menu);

#endif // MENU_H