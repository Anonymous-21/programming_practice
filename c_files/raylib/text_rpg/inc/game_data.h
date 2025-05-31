#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef enum GameState
{
	STATE_MAIN_MENU,
	STATE_PLAYER_SELECTION,
	STATE_TOWN,
	STATE_QUIT

} GameState;

// main menu items
extern const char* main_menu_array[];
extern const int main_menu_array_size;

// hero data
typedef struct BaseHero
{
	const char* type;
	const float health;
	const float damage;
	const float defense;
	const float health_growth;
	const float damage_growth;
	const float defense_growth;

} BaseHero;

extern const BaseHero hero_array[];
extern const int hero_array_size;

const char**
initialize_player_selection_menu();

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

extern const BaseEnemy enemy_array[];
extern const int enemy_array_size;

#endif // GAME_DATA_H;
