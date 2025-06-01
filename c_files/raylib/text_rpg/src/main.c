#include "../inc/game_data.h"
#include "../inc/menu.h"
#include "../inc/player-selection_details.h"
#include "../inc/player.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;
    const char SCREEN_TITLE[] = "Text Rpg";
    const Color SCREEN_BACKGROUND = RAYWHITE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameState current_state = STATE_MAIN_MENU;
    int menu_margin = 40; // 20 up and 20 down
    bool player_selected = false;

    ShopType current_shop_type = SHOP_INVALID;
    MapZone current_map_zone = SHOP_INVALID;

    Menu main_menu;
    Menu player_selection_menu;
    Menu town_menu;
    Menu map_menu;
    // Menu quest_menu;
    Menu shop_menu;

    Player player;

    menu_init(&main_menu,
              main_menu_items,
              main_menu_items_size,
              40,
              10,
              (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_margin });

    const char** player_selection_menu_items = malloc(hero_types_size * sizeof(const char*));
    if (player_selection_menu_items == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < hero_types_size; i++)
    {
        player_selection_menu_items[i] = hero_types[i].type;
    }

    menu_init(&player_selection_menu,
              player_selection_menu_items,
              hero_types_size,
              30,
              20,
              (Rectangle){ 0, 0, GetScreenWidth() / 2, GetScreenHeight() - menu_margin });

    menu_init(&town_menu,
              town_menu_items,
              town_menu_items_size,
              30,
              20,
              (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_margin });

    menu_init(&map_menu,
              map_menu_items,
              map_menu_items_size,
              30,
              20,
              (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_margin });

    menu_init(&shop_menu,
              shop_menu_items,
              shop_menu_items_size,
              30,
              20,
              (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_margin });

    while (current_state != STATE_QUIT)
    {
        if (IsKeyPressed(KEY_ESCAPE) && player_selected)
        {
            current_state--;
            if (current_state == 1)
            {
                current_state = 0;
            }
            if (current_state > 2 && current_state != STATE_QUIT)
            {
                current_state = 2;
            }
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        switch (current_state)
        {
            case STATE_MAIN_MENU:

                menu_draw(&main_menu);
                menu_update(&main_menu);
                if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                    current_state == STATE_MAIN_MENU)
                {
                    switch (main_menu.selected)
                    {
                        case 0:
                            current_state = STATE_PLAYER_SELECTION;
                            break;

                        case 1:
                            if (player_selected)
                            {
                                current_state = STATE_TOWN;
                            }
                            break;

                        case 2:
                            current_state = STATE_QUIT;
                            break;
                    }
                }
                break;

            case STATE_PLAYER_SELECTION:

                menu_draw(&player_selection_menu);
                menu_update(&player_selection_menu);
                draw_player_selection_details(player_selection_menu.selected);

                if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                    current_state == STATE_PLAYER_SELECTION)
                {
                    player_init(&player, player_selection_menu.selected);
                    player_selected = true;
                    current_state = STATE_TOWN;
                }
                break;

            case STATE_TOWN:

                menu_draw(&town_menu);
                menu_update(&town_menu);
                if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                    current_state == STATE_TOWN)
                {
                    switch (town_menu.selected)
                    {
                        case 0:
                            current_state = STATE_MAP;
                            break;
                        case 1:
                            current_state = STATE_QUEST;
                            break;
                        case 2:
                            current_state = STATE_SHOP;
                            break;
                    }
                }
                break;

            case STATE_MAP:

                menu_draw(&map_menu);
                menu_update(&map_menu);
                if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                    current_state == STATE_MAP)
                {
                    switch (map_menu.selected)
                    {
                        case 0:
                            current_map_zone = MAP_ZONE_SETTLEMENTS;
                            break;
                        case 1:
                            current_map_zone = MAP_ZONE_WILDERNESS;
                            break;
                        case 2:
                            current_map_zone = MAP_ZONE_DUNGEONS;
                            break;
                        case 3:
                            current_map_zone = MAP_ZONE_MYSTICAL;
                            break;
                        case 4:
                            current_map_zone = MAP_ZONE_CONFLICT;
                            break;
                    }
                }
                break;
            case STATE_QUEST:
                break;
            case STATE_SHOP:
                menu_draw(&shop_menu);
                menu_update(&shop_menu);
                if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                    current_state == STATE_SHOP)
                {
                    switch (shop_menu.selected)
                    {
                        case 0:
                            current_shop_type = SHOP_TYPE_CONSUMABLES;
                            break;
                        case 1:
                            current_shop_type = SHOP_TYPE_WEAPONS;
                            break;
                        case 2:
                            current_shop_type = SHOP_TYPE_ARMORS;
                            break;
                        case 3:
                            current_shop_type = SHOP_TYPE_ACCESSORIES;
                            break;
                    }
                }
                break;

            case STATE_QUIT:
                break;
        }

        EndDrawing();
    }

    free(player_selection_menu_items);
    player_selection_menu_items = NULL;

    menu_free(&main_menu);
    menu_free(&player_selection_menu);
    menu_free(&town_menu);
    menu_free(&map_menu);

    CloseWindow();

    return 0;
}
