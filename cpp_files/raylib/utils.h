#ifndef INTERVAL_TIMER_H
#define INTERVAL_TIMER_H

#include <raylib.h>

typedef struct IntervalTimer
{
    float duration;
    float last_updated_time;
    bool current_state;

}IntervalTimer;

void interval_timer_init(IntervalTimer *interval_timer, float duration);
void interval_timer_update(IntervalTimer *interval_timer);
bool interval_timer_toggled(IntervalTimer * interval_timer);

void
center_and_draw_text(const char* text, int font_size, Rectangle layout_rect, Color color = BLACK);

#endif // INTERVAL_TIMER_H