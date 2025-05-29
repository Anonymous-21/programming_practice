#include "../include/player.h"
#include "../include/game_data.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
player_init(Player* player, const char* type)
{
	for (int i = 0; i < player_menu_items_count; i++) {
		if (type != NULL && strncmp(type,
									player_menu_items[i].type,
									strlen(player_menu_items[i].type) == 0)) {
			player->type = player_menu_items[i].type;
			player->max_health = player_menu_items[i].health;
			player->current_health = player->max_health;
			player->damage = player_menu_items[i].damage;
            player->defense = player_menu_items[i].defense;
			player->health_growth = player_menu_items[i].health_growth;
			player->damage_growth = player_menu_items[i].damage_growth;
		}
	}
}

bool
player_is_alive(Player* player)
{
	return player->current_health > 0;
}