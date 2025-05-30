#include "../include/menu.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void
menu_init(Menu* menu,
		  const char* item_arr[],
		  int item_size,
		  int font_size,
		  Rectangle layout_rect)
{
	menu->selected = 0;
	menu->vertical_gap = 50;
	menu->layout_rect = layout_rect;
	menu->item_size = item_size;

	menu->items = malloc(item_size * sizeof(MenuItem));
	if (menu->items == NULL) {
		fprintf(stderr, "Memory not allocated to menu->items\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < item_size; i++) {
		menu->items[i].title = item_arr[i];
		menu->items[i].font_size = font_size;
		menu->items[i].width = MeasureText(item_arr[i], font_size);
		menu->items[i].x = (int)layout_rect.x + (int)layout_rect.width / 2 -
						   menu->items[i].width / 2;
		menu->items[i].y = (int)layout_rect.y + (int)layout_rect.height / 2 -
						   font_size / 2 + (i * menu->vertical_gap) -
						   menu->vertical_gap / 2;
	}
}

void
menu_draw(Menu* menu)
{
	for (int i = 0; i < menu->item_size; i++) {
		// draw items
		Color color = (i == menu->selected) ? BLACK : GRAY;

		DrawText(menu->items[i].title,
				 menu->items[i].x,
				 menu->items[i].y,
				 menu->items[i].font_size,
				 color);

		// draw selection arrow
		if (i == menu->selected) {
			int arrow_margin = 30;
			int arrow_font_size = 40;
			Color arrow_color = BLACK;
			DrawText(">",
					 menu->items[i].x - arrow_margin,
					 menu->items[i].y,
					 arrow_font_size,
					 arrow_color);
		}
	}
}

void
menu_update(Menu* menu)
{
	if (IsKeyPressed(KEY_UP)) {
		menu->selected =
		  (menu->selected - 1 + menu->item_size) % menu->item_size;
	}
	if (IsKeyPressed(KEY_DOWN)) {
		menu->selected = (menu->selected + 1) % menu->item_size;
	}
}

void
menu_free(Menu* menu)
{
	free(menu->items);
	menu->items = NULL;
}