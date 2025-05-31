#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef struct MenuItem
{
	const char* title;
	int width;
	int x;
	int y;

} MenuItem;

typedef struct Menu
{
	MenuItem* items;
	int arr_size;
	int font_size;
	int line_gap;
	int line_height;
	int margin;
	int selected;
	int first_visible_element;
	int max_visible_elements;
	int visible_text_height;
	Rectangle layout_rect;

} Menu;

void
menu_init(Menu* menu,
		  const char* arr[],
		  int arr_size,
		  int font_size,
		  int line_gap,
		  int margin,
		  Rectangle layout_rect);
void
menu_draw(Menu* menu);
void
menu_update(Menu* menu);
void
menu_free(Menu* menu);

#endif // MENU_H