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

    const char* health = TextFormat("Health: %.2f", hero_types[selected].health);
    const char* damage = TextFormat("Damage: %.2f", hero_types[selected].damage);
    const char* defense = TextFormat("Defense: %.2f", hero_types[selected].defense);
    const char* health_growth =
      TextFormat("Health Growth: %.2f", hero_types[selected].health_growth);
    const char* damage_growth =
      TextFormat("Damage Growth: %.2f", hero_types[selected].damage_growth);
    const char* defense_growth =
      TextFormat("Defense Growth: %.2f", hero_types[selected].defense_growth);

    const char* arr[] = { health, damage, defense, health_growth, damage_growth, defense_growth };
    const int arr_size = sizeof(arr) / sizeof(arr[0]);
    int margin = 40;

    center_and_draw_text_array(
      arr,
      arr_size,
      30,
      20,
      (Rectangle){ GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight() - margin },
      BLACK);
}