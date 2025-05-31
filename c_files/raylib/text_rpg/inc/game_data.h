#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef enum GameState
{
    STATE_MAIN_MENU,
    STATE_PLAYER_SELECTION,
    STATE_TOWN,
    STATE_QUIT

} GameState;

// main menu data
extern const char* main_menu_items[];
extern const int main_menu_items_size;

// player data
typedef struct BaseHero
{
    const char* type;
    const char* roles;
    const float health;
    const float damage;
    const float defense;
    const float health_growth;
    const float damage_growth;
    const float defense_growth;
    const char* notes;

} BaseHero;

const BaseHero hero_types[];
extern const int hero_types_size;

// enemy data
typedef struct BaseEnemy
{
    const char* type;
    const float health;
    const float damage;
    const float defense;
    const float health_growth;
    const float damage_growth;
    const float defense_growth;

} BaseEnemy;

const BaseEnemy enemy_types[];
extern const int enemy_types_size;

#endif // GAME_DATA_H