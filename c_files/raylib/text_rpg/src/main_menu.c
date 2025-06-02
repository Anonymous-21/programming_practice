#include "../inc/main_menu.h"
#include "../inc/game_states.h"
#include "../inc/menu.h"
#include <raylib.h>

typedef enum
{
    NEW_GAME,
    CONTINUE,
    QUIT,

} MainMenuState;

static Menu main_menu;
static const char* const main_menu_database[] = { "NEW GAME", "CONTINUE", "QUIT" };
static const int main_menu_database_size =
  sizeof(main_menu_database) / sizeof(main_menu_database[0]);

void
main_menu_init(int menu_vertical_padding)
{
    int font_size = 40;
    int text_gap = 20;
    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() - menu_vertical_padding };

    menu_init(
      &main_menu, main_menu_database, main_menu_database_size, font_size, text_gap, layout_rect);
}

void
main_menu_draw()
{
    menu_draw(&main_menu);
}

void
main_menu_update(GameState* current_state, bool player_selected)
{
    menu_update(&main_menu);
    if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) &&
        *current_state == STATE_MAIN_MENU)
    {
        switch (main_menu.selected)
        {
            case NEW_GAME:
                *current_state = STATE_PLAYER_SELECTION;
                break;

            case CONTINUE:
                if (player_selected)
                {
                    *current_state = STATE_TOWN;
                }
                else
                {
                    main_menu.color = GRAY;
                }
                break;

            case QUIT:
                *current_state = STATE_QUIT;
                break;

            default:
                TraceLog(LOG_WARNING, "Invalied main menu selection: %d\n", main_menu.selected);
        }
    }
}

void
main_menu_free()
{
    menu_free(&main_menu);
}