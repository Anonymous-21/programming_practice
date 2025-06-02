#include "../inc/player_selection_menu.h"
#include "../inc/hero_types_database.h"
#include "../inc/menu.h"
#include "../inc/player.h"
#include "../inc/utils.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum PlayerSelectionState
{
    WARRIOR,
    RANGER,
    MAGE,
    CLERIC,
    ROGUE,
    PALADIN,
    BERSERKER,
    NECROMANCER,
    DRUID,
    MONK

} PlayerSelectionState;

static Menu player_selection_menu;

static void
draw_hero_type_summary(int selected)
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
    int vertical_padding = 40;
    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect = (Rectangle){
        GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight() - vertical_padding
    };
    Color color = BLACK;

    center_and_draw_text_array(arr, arr_size, font_size, text_gap, layout_rect, color);
}

void
player_selection_init(int menu_vertical_padding)
{
    char** temp_arr = malloc(hero_types_size * sizeof(char*));
    if (temp_arr == NULL)
    {
        fprintf(stderr, "Memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < hero_types_size; i++)
    {
        temp_arr[i] = hero_types[i].type;
    }

    int font_size = 30;
    int text_gap = 20;
    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth() / 2.0f, GetScreenHeight() - menu_vertical_padding };

    menu_init(&player_selection_menu,
              ( const char* const* ) temp_arr,
              hero_types_size,
              font_size,
              text_gap,
              layout_rect);

    free(temp_arr);
    temp_arr = NULL;
}

void
player_selection_draw()
{
    menu_draw(&player_selection_menu);
}

Player
player_selection_update(GameState* current_state, bool* player_selected)
{
    menu_update(&player_selection_menu);
    draw_hero_type_summary(player_selection_menu.selected);

    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
        *current_state == STATE_PLAYER_SELECTION)
    {
        *player_selected = true;
        *current_state = STATE_TOWN;
        
        return player_init(player_selection_menu.selected);
    }
}

void
player_selection_free()
{
    menu_free(&player_selection_menu);
}
