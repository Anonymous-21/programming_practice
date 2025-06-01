#ifndef PLAYER_H
#define PLAYER_H

#include "game_data.h"
#include <stdbool.h>

typedef struct Player
{
    const char * type;
    float max_health;
    float health;
    float damage;
    float defense;
    float health_growth;
    float damage_growth;
    float defense_growth;

}Player;

void player_init(Player *player, int selected);
bool player_is_alive(Player * player);
void player_draw(Player *player);
void Player_update(Player *player);

#endif // PLAYER_H;