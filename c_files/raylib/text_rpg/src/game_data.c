#include "../inc/game_data.h"

// quests menu data
char* quest_menu_items[] = { 0 };
int quest_menu_items_size = sizeof(quest_menu_items) / sizeof(quest_menu_items[0]);

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
