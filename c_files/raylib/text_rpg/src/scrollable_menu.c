#include "../inc/scrollable_menu.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void
scrollable_menu_init(ScrollableMenu* scrollable_menu,
                     int font_size,
                     int line_gap,
                     int margin,
                     Rectangle layout_rect)
{
    scrollable_menu->font_size = font_size;
    scrollable_menu->line_gap = line_gap;
    scrollable_menu->line_height = font_size + line_gap;
    scrollable_menu->margin = margin;
    scrollable_menu->layout_rect = layout_rect;
    scrollable_menu->selected = 0;
    scrollable_menu->first_visible_element = 0;
    scrollable_menu->max_visible_elements =
      (layout_rect.height - line_gap - margin * 2) /
      scrollable_menu->line_height;
    scrollable_menu->max_visible_height =
      (font_size * scrollable_menu->max_visible_elements) +
      (line_gap * (scrollable_menu->max_visible_elements - 1));
}

void
scrollable_menu_draw(ScrollableMenu* scrollable_menu, const char * arr[], int arr_size)
{
    int last_visible_element = scrollable_menu->first_visible_element +
                               scrollable_menu->max_visible_elements - 1;
    for (int i = scrollable_menu->first_visible_element;
         i < scrollable_menu->arr_size && i < last_visible_element;
         i++) {

        int text_width =
          MeasureText(arr[i], scrollable_menu->font_size);
        int text_x = (int)scrollable_menu->layout_rect.x +
                     (int)scrollable_menu->layout_rect.width / 2 -
                     text_width / 2;
        int text_y = (int)scrollable_menu->layout_rect.y +
                     (int)scrollable_menu->layout_rect.height / 2 -
                     scrollable_menu->max_visible_height / 2 +
                     (i - scrollable_menu->first_visible_element) *
                       scrollable_menu->line_height;

        Color color = (i == scrollable_menu->selected) ? BLACK : GRAY;

        // draw menu item
        DrawText(arr[i],
                 text_x,
                 text_y,
                 scrollable_menu->font_size,
                 color);

        if (i == scrollable_menu->selected) {
            // draw selection arrow
            DrawText(
              ">", text_x - 30, text_y, scrollable_menu->font_size, color);
        }
    }
}

void
scrollable_menu_update(ScrollableMenu* scrollable_menu)
{
    if (IsKeyPressed(KEY_UP)) {
        scrollable_menu->selected--;
        if (scrollable_menu->selected <= 0) {
            scrollable_menu->selected = 0;
        }

        if (scrollable_menu->selected <=
            scrollable_menu->first_visible_element) {
            scrollable_menu->first_visible_element = scrollable_menu->selected;
        }
    }

    if (IsKeyPressed(KEY_DOWN)) {
        scrollable_menu->selected++;
        if (scrollable_menu->selected >= scrollable_menu->arr_size - 1) {
            scrollable_menu->selected = scrollable_menu->arr_size - 1;
        }

        if (scrollable_menu->selected >=
            scrollable_menu->first_visible_element +
              scrollable_menu->max_visible_elements) {
            scrollable_menu->first_visible_element++;
        }
    }
}
