#ifndef SCROLLABLE_MENU_H
#define SCROLLABLE_MENU_H

#include <raylib.h>
#include "../inc/game_data.h"

typedef struct ScrollableMenu
{
	int arr_size;
	int font_size;
	int line_gap;
	int line_height;
	int margin;
	int selected;
	int first_visible_element;
	int max_visible_elements;
	int max_visible_height;
	Rectangle layout_rect;

} ScrollableMenu;

void
scrollable_menu_init(ScrollableMenu* scrollable_menu,
					 int font_size,
					 int line_gap,
					 int margin,
					 Rectangle layout_rect);

void
scrollable_menu_draw(ScrollableMenu* scrollable_menu, const char* arr[], int arr_size);
void
scrollable_menu_update(ScrollableMenu* scrollable_menu);
void
scrollable_menu_free(ScrollableMenu* scrollable_menu);

#endif // SCROLLABLE_MENU_H
