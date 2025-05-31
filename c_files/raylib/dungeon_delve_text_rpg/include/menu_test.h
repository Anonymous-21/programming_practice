#ifndef MENU_TEST_H
#define MENU_TEST_H

#include <raylib.h>

typedef struct ScrollableMenu
{
	int arr_size;
	char** arr;
	int font_size;
	int line_gap;
	int margin;
	int selected_element;
	int first_visible_element;
	int maximum_visible_elements;
	Rectangle layout_rect;

} ScrollableMenu;

void
scrollable_menu_init(ScrollableMenu* scrollable_menu,
					 char** arr,
					 int arr_size,
					 int font_size,
					 int line_gap,
					 int margin);
void
scrollable_menu_draw(ScrollableMenu* scrollable_menu);
void
scrollable_menu_update(ScrollableMenu* scrollable_menu);
void
scrollable_menu_free(ScrollableMenu* scrollable_menu);

#endif // MENU_TEST_H