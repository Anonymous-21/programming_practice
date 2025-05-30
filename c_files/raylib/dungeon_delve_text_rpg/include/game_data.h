#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef enum GameState
{
    STATE_MAIN_MENU,
    STATE_PLAYER_TYPE_SELECTION,
    STATE_TOWN,
    STATE_SHOP,
    STATE_ACTION_SCREEN,

}GameState;

// MAIN MENU ITEMS
extern const char* main_menu_items[] = { "NEW GAME", "QUIT" };

extern const int main_menu_item_count =
  sizeof(main_menu_items) / sizeof(main_menu_items[0]);

// PLAYER SELECTION MENU ITEMS
extern const char* player_selection_menu_items[] = { "Warrior", "Ranger", "Mage" };

extern const int player_selection_menu_item_count =
  sizeof(player_selection_menu_items) / sizeof(player_selection_menu_items[0]);

#endif // GAME_DATA_H