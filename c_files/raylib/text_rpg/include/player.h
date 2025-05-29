#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct Player
{
	const char* type;
	float max_health;
	float current_health;
	float damage;
	float defense;
	float health_growth;
	float damage_growth;

} Player;

void
player_init(Player* player, const char* type);
bool
player_is_alive(Player* player);
void
player_attack(Player* player);
void
player_defend(Player* player);
void
player_update(Player* player);

#endif // PLAYER_H