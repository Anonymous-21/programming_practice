#include "../include/game_data.h"

// MAIN MENU
const char* main_menu_items[] = { "NEW GAME", "QUIT" };

const int main_menu_items_count =
  sizeof(main_menu_items) / sizeof(main_menu_items[0]);

// PLAYER MENU ITEMS
const BasePlayer player_menu_items[] = {
	{ "Warrior", 90, 8, 10, 1.12, 1.06 },
	{ "Ranger", 60, 11, 4, 1.08, 1.12 },
	{ "Mage", 50, 14, 3, 1.05, 1.15 },
	{ "Cleric", 65, 6, 6, 1.10, 1.04 },
	{ "Rogue", 55, 13, 5, 1.07, 1.14 },
	{ "Paladin", 80, 9, 9, 1.11, 1.08 },
	{ "Berserker", 70, 12, 7, 1.10, 1.13 },
	{ "Necromancer", 50, 10, 4, 1.06, 1.10 },
	{ "Druid", 65, 9, 6, 1.10, 1.09 },
	{ "Monk", 60, 10, 6, 1.09, 1.10 }
};

const int player_menu_items_count =
  sizeof(player_menu_items) / sizeof(player_menu_items[0]);

// ENEMY MENU ITEMS
const BaseEnemy enemy_menu_items[] = {
	{ "Zombie", 50, 5, 4, 1.10, 1.05 },	   { "Goblin", 40, 7, 3, 1.08, 1.06 },
	{ "Skeleton", 45, 6, 4, 1.09, 1.05 },  { "Orc", 70, 10, 6, 1.12, 1.08 },
	{ "Troll", 100, 8, 7, 1.15, 1.04 },	   { "Vampire", 65, 12, 5, 1.10, 1.10 },
	{ "Werewolf", 80, 11, 6, 1.12, 1.09 }, { "Demon", 90, 14, 7, 1.13, 1.12 },
	{ "Dragon", 150, 20, 10, 1.18, 1.15 }, { "Bandit", 55, 9, 4, 1.09, 1.07 },
	{ "Witch", 60, 13, 3, 1.08, 1.13 }
};

const int enemy_menu_items_count =
  sizeof(enemy_menu_items) / sizeof(enemy_menu_items[0]);