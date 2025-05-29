#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef enum GameState
{
	STATE_MAIN_MENU,
	STATE_PLAYER_SELECTION,
	STATE_TOWN,
	STATE_GAME_QUIT

} GameState;

typedef struct BasePlayer
{
	const char* type;
	const float health;
	const float damage;
	const float defense;
	const float health_growth;
	const float damage_growth;

} BasePlayer;

typedef struct BaseEnemy
{
	const char* type;
	const float health;
	const float damage;
	const float defense;
	const float health_growth;
	const float damage_growth;

} BaseEnemy;

extern const char* main_menu_items[];
extern const int main_menu_items_count;

extern const BasePlayer player_menu_items[];
extern const int player_menu_items_count;

extern const BaseEnemy enemy_menu_items[];
extern const int enemy_menu_items_count;

#endif // GAME_DATA_H