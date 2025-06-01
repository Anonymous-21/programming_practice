#include "../inc/player.h"

void
player_init(Player* player, int selected)
{
    player->type = hero_types[selected].type;
    player->max_health = hero_types[selected].health;
    player->health = player->max_health;
    player->damage = hero_types[selected].damage;
    player->defense = hero_types[selected].defense;
    player->health_growth = hero_types[selected].health_growth;
    player->damage_growth = hero_types[selected].damage_growth;
    player->defense_growth = hero_types[selected].defense_growth;
}

bool
player_is_alive(Player* player)
{
    return player->health > 0;
}