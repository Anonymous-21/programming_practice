#include "../inc/game_data.h"
#include "../inc/menu.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char SCREEN_TITLE[] = "Text Rpg";
    const Color SCREEN_BACKGROUND = RAYWHITE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameState current_state = STATE_MAIN_MENU;
    int menu_margin = 40; // 20 up and 20 down

    Menu main_menu;
    Menu player_selection_menu;

    menu_init(&main_menu,
              main_menu_items,
              main_menu_items_size,
              40,
              5,
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
              40,
              5,
              (Rectangle){ 0, 0, GetScreenWidth() / 2, GetScreenHeight() - menu_margin});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        if (current_state == STATE_MAIN_MENU)
        {
            menu_draw(&main_menu);
            menu_update(&main_menu);
            if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                current_state == STATE_MAIN_MENU)
            {
                if (main_menu.selected == 0)
                {
                    current_state = STATE_PLAYER_SELECTION;
                }
                else if (main_menu.selected == 1)
                {
                    current_state = STATE_QUIT;
                }
            }
        }
        else if (current_state == STATE_PLAYER_SELECTION)
        {
            menu_draw(&player_selection_menu);
            menu_update(&player_selection_menu);
            if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
                current_state == STATE_PLAYER_SELECTION)
            {
                current_state = STATE_TOWN;
            }
        }
        else if (current_state == STATE_QUIT)
        {
            break;
        }

        EndDrawing();
    }

    free(player_selection_menu_items);
    player_selection_menu_items = NULL;

    menu_free(&main_menu);
    menu_free(&player_selection_menu);

    CloseWindow();

    return 0;
}
