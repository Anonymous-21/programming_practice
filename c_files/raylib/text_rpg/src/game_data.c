#include "../inc/game_data.h"
#include <stdio.h>
#include <stdlib.h>

// main menu items
const char* main_menu_array[] = { "NEW GAME", "QUIT" };

const int main_menu_array_size =
  sizeof(main_menu_array) / sizeof(main_menu_array[0]);

// hero data
const BaseHero hero_array[] = { { "Warrior", 90, 8, 10, 1.12, 1.06, 1.10 },
								{ "Ranger", 60, 11, 4, 1.08, 1.12, 1.04 },
								{ "Mage", 50, 14, 3, 1.05, 1.15, 1.03 },
								{ "Cleric", 65, 6, 6, 1.10, 1.04, 1.07 },
								{ "Rogue", 55, 13, 5, 1.07, 1.14, 1.05 },
								{ "Paladin", 80, 9, 9, 1.11, 1.08, 1.09 },
								{ "Berserker", 70, 12, 7, 1.10, 1.13, 1.06 },
								{ "Necromancer", 50, 10, 4, 1.06, 1.10, 1.04 },
								{ "Druid", 65, 9, 6, 1.10, 1.09, 1.06 },
								{ "Monk", 60, 10, 6, 1.09, 1.10, 1.06 } };

const int hero_array_size = sizeof(hero_array) / sizeof(hero_array[0]);

// player selection menu array
const char**
initialize_player_selection_menu()
{
	char* copy[] = malloc(hero_array_size * sizeof(char**));
	if (copy == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < hero_array_size; i++) {
		copy[i] = malloc(sizeof(char*));
		if (copy[i] == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		copy[i] = hero_array[i].type; // type = const char * type;
	}

	return copy;
}

// enemy data
const BaseEnemy enemy_array[] = { { "Zombie", 50, 5, 4, 1.10, 1.05, 1.04 },
								  { "Goblin", 40, 7, 3, 1.08, 1.06, 1.03 },
								  { "Skeleton", 45, 6, 4, 1.09, 1.05, 1.04 },
								  { "Orc", 70, 10, 6, 1.12, 1.08, 1.06 },
								  { "Troll", 100, 8, 7, 1.15, 1.04, 1.07 },
								  { "Vampire", 65, 12, 5, 1.10, 1.10, 1.05 },
								  { "Werewolf", 80, 11, 6, 1.12, 1.09, 1.06 },
								  { "Demon", 90, 14, 7, 1.13, 1.12, 1.07 },
								  { "Dragon", 150, 20, 10, 1.18, 1.15, 1.10 },
								  { "Bandit", 55, 9, 4, 1.09, 1.07, 1.04 },
								  { "Witch", 60, 13, 3, 1.08, 1.13, 1.03 } };

const int enemy_array_size = sizeof(enemy_array) / sizeof(enemy_array[0]);
