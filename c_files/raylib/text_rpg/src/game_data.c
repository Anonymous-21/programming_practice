#include "../inc/game_data.h"

// town menu data
const char* const town_menu_items[] = { "MAP", "QUEST", "SHOP" };
const int town_menu_items_size = sizeof(town_menu_items) / sizeof(town_menu_items[0]);

// ship menu data
const char* const shop_menu_items[] = { "CONSUMABLES", "WEAPONS", "ARMORS", "ACCESSORIES" };
const int shop_menu_items_size = sizeof(shop_menu_items) / sizeof(shop_menu_items[0]);

// quests menu data
char* quest_menu_items[] = { 0 };
int quest_menu_items_size = sizeof(quest_menu_items) / sizeof(quest_menu_items[0]);

// map menu data
const char* const map_menu_items[] = { "Settlements",
                                       "Wilderness",
                                       "Dungeons",
                                       "Mystical",
                                       "Conflict Zones" };
const int map_menu_items_size = sizeof(map_menu_items) / sizeof(map_menu_items[0]);

const char* const zone_settlement_items[] = { "Windmere Village",
                                              "Ironhold",
                                              "Thornbridge",
                                              "Duskwatch",
                                              "Serpents Rest" };
const int zone_settlement_items_size =
  sizeof(zone_settlement_items) / sizeof(zone_settlement_items[0]);

const char* const zone_wilderness_items[] = { "The Whispering Woods",
                                              "Frostveil Glacier",
                                              "The Scorched Expanse",
                                              "Starfall Crater",
                                              "Moonlit Grove" };
const int zone_wilderness_items_size =
  sizeof(zone_wilderness_items) / sizeof(zone_wilderness_items[0]);

const char* const zone_dungeon_items[] = { "The Hollow Keep",
                                           "Caverns of the Wyrm",
                                           "Sunken Sanctum",
                                           "Obsidian Spire",
                                           "Vault of Forgotten Kings" };
const int zone_dungeon_items_size = sizeof(zone_dungeon_items) / sizeof(zone_dungeon_items[0]);

const char* const zone_mystical_items[] = { "The Shattered Isles",
                                            "The Arcane Nexus",
                                            "Mirrorlake",
                                            "Chronos Ruins",
                                            "The Labyrinth of Echoes" };
const int zone_mystical_items_size = sizeof(zone_mystical_items) / sizeof(zone_mystical_items[0]);

const char* const zone_conflict_items[] = { "Redridge Battlefield",
                                            "The Crimson Marsh",
                                            "Grave of Giants",
                                            "Broken Banner Fort",
                                            "Ashen Fields" };
const int zone_conflict_items_size = sizeof(zone_conflict_items) / sizeof(zone_conflict_items[0]);

// enemy data
const BaseEnemy enemy_types[] = {
    { "Zombie", 50, 5, 1.10f, 1.05f, 4, 1.05f },    { "Goblin", 40, 7, 1.08f, 1.06f, 2, 1.03f },
    { "Skeleton", 45, 6, 1.09f, 1.05f, 3, 1.04f },  { "Orc", 70, 10, 1.12f, 1.08f, 6, 1.07f },
    { "Troll", 100, 8, 1.15f, 1.04f, 8, 1.06f },    { "Vampire", 65, 12, 1.10f, 1.10f, 5, 1.08f },
    { "Werewolf", 80, 11, 1.12f, 1.09f, 6, 1.07f }, { "Demon", 90, 14, 1.13f, 1.12f, 7, 1.09f },
    { "Dragon", 150, 20, 1.18f, 1.15f, 10, 1.10f }, { "Bandit", 55, 9, 1.09f, 1.07f, 3, 1.05f },
    { "Witch", 60, 13, 1.08f, 1.13f, 4, 1.06f }
};
const int enemy_types_size = sizeof(enemy_types) / sizeof(enemy_types[0]);
