#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

static inline void
center_and_draw_text(const char* text,
					 int font_size,
					 Rectangle source_rect,
					 Color color)
{
	int text_width = MeasureText(text, font_size);
	int text_x =
	  (int)source_rect.x + (int)source_rect.width / 2 - text_width / 2;
	int text_y =
	  (int)source_rect.y + (int)source_rect.height / 2 - font_size / 2;

	DrawText(text, text_x, text_y, font_size, color);
}

#endif // UTILS_H