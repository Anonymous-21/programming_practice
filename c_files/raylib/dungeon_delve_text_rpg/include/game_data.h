#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef enum GameState
{
	STATE_MAIN_MENU,
	STATE_PLAYER_TYPE_SELECTION,
	STATE_TOWN,
	STATE_SHOP,
	STATE_ACTION_SCREEN,

} GameState;

// HERO DATA
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

// GLOBAL HERO ARRAY
extern const BaseHero hero_array[];
extern const int hero_array_size;

// ENEMY DATA
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

// GLOBAL ENEMY ARRAY
extern const BaseEnemy enemy_array[];
extern const int enemy_array_size;

// MAIN MENU ITEMS
extern const char* main_menu_items[];
extern const int main_menu_item_size;

#endif // GAME_DATA_H