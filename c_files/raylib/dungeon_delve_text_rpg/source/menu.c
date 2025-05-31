#include "../include/menu.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void
menu_init(Menu* menu,
		  const char* arr[],
		  int arr_size,
		  int font_size,
		  int line_gap,
		  int margin,
		  Rectangle layout_rect)
{
	menu->arr_size = arr_size;
	menu->selected = 0;
	menu->first_visible_element = 0;
	menu->font_size = font_size;
	menu->line_gap = line_gap;
	menu->line_height = font_size + line_gap;
	menu->margin = margin;
	menu->layout_rect = layout_rect;
	menu->max_visible_elements =
	  (layout_rect.height - line_gap - margin * 2) / menu->line_height;
	menu->visible_text_height =
	  (font_size * arr_size) + (line_gap * (arr_size - 1));

	menu->items = malloc(arr_size * sizeof(MenuItem));
	if (menu->items == NULL) {
		fprintf(stderr, "Memory not allocated to menu->items\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < arr_size; i++) {
		menu->items[i].title = arr[i];
		menu->items[i].width = MeasureText(arr[i], font_size);
		menu->items[i].x = (int)layout_rect.x + (int)layout_rect.width / 2 -
						   menu->items[i].width / 2;
	}
}

void
menu_draw(Menu* menu)
{
	int last_visible_element =
	  menu->first_visible_element + menu->max_visible_elements - 1;

	for (int i = menu->first_visible_element;
		 i < menu->arr_size && i < last_visible_element;
		 i++) {
		menu->items[i].y =
		  (int)menu->layout_rect.y + (int)menu->layout_rect.height / 2 -
		  menu->visible_text_height / 2 +
		  (i - menu->first_visible_element) * menu->line_height;

		// draw items
		Color color = (i == menu->selected) ? BLACK : GRAY;

		DrawText(menu->items[i].title,
				 menu->items[i].x,
				 menu->items[i].y,
				 menu->font_size,
				 color);

		// draw selection arrow
		if (i == menu->selected) {
			int arrow_margin = 30;
			DrawText(">",
					 menu->items[i].x - arrow_margin,
					 menu->items[i].y,
					 menu->font_size,
					 color);
		}
	}
}

void
menu_update(Menu* menu)
{
	if (IsKeyPressed(KEY_UP)) {
		menu->selected--;
		if (menu->selected <= 0) {
			menu->selected = 0;
		}

		if (menu->selected < menu->first_visible_element) {
			menu->first_visible_element = menu->selected;
		}
	}
	if (IsKeyPressed(KEY_DOWN)) {
		menu->selected++;
		if (menu->selected > menu->arr_size - 1) {
			menu->selected = menu->arr_size - 1;
		}

		if (menu->selected >
			menu->first_visible_element + menu->max_visible_elements - 1) {
			menu->first_visible_element++;
		}
	}
}

void
menu_free(Menu* menu)
{
	free(menu->items);
	menu->items = NULL;
}