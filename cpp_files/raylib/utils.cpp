#include "utils.h"
#include <raylib.h>

// interval timer
void interval_timer_init(IntervalTimer * interval_timer, float duration)
{
    interval_timer->duration = duration;
    interval_timer->last_updated_time = GetTime();
    interval_timer->current_state = false;
}

void interval_timer_update(IntervalTimer *interval_timer)
{
    float current_time = GetTime();
    if (current_time - interval_timer->last_updated_time >= interval_timer->duration)
    {
        interval_timer->current_state = !interval_timer->current_state;
        interval_timer->last_updated_time = current_time;
    }
}

bool interval_timer_toggled(IntervalTimer *interval_timer)
{
    return interval_timer->current_state;
}

// draw text
void
center_and_draw_text(const char* text, int font_size, Rectangle layout_rect, Color color)
{
    int text_width = MeasureText(text, font_size);
    int text_x = layout_rect.x + layout_rect.width / 2 - text_width / 2;
    int text_y = layout_rect.y + layout_rect.height / 2 - font_size / 2;

    DrawText(text, text_x, text_y, font_size, color);
}