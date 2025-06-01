#include "../inc/game_data.h"
#include "../inc/player-selection_details.h"
#include "../inc/utils.h"
#include <raylib.h>

void
draw_player_selection_details(int selected)
{
    // draw line divider
    DrawLineEx((Vector2){ GetScreenWidth() / 2, 0 },
               (Vector2){ GetScreenWidth() / 2, GetScreenHeight() },
               5.0,
               BLACK);

    const char* health = TextFormat("%.2f", hero_types[selected].health);
    const char* damage = TextFormat("%.2f", hero_types[selected].damage);
    const char* defense = TextFormat("%.2f", hero_types[selected].defense);
    const char* health_growth = TextFormat("%.2f", hero_types[selected].health_growth);
    const char* damage_growth = TextFormat("%.2f", hero_types[selected].damage_growth);
    const char* defense_growth = TextFormat("%.2f", hero_types[selected].defense_growth);

    const char* arr[] = { hero_types[selected].type,
                          health,
                          damage,
                          defense,
                          health_growth,
                          damage_growth,
                          defense_growth };
    int margin = 40;

    center_and_draw_text_array(
      arr,
      40,
      5,
      (Rectangle){ GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight() - margin },
      BLACK);
}