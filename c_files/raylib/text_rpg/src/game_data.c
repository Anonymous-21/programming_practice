#include "../include/game_data.h"

// quests menu data
char* quest_menu_items[] = { 0 };
int quest_menu_items_size = sizeof(quest_menu_items) / sizeof(quest_menu_items[0]);

const char* const zone_settlement_items[] = { "WINDMERE VILLAGE",
                                              "IRONHOLD",
                                              "THORNBRIDGE",
                                              "DUSKWATCH",
                                              "SERPENTS REST" };
const int zone_settlement_items_size =
  sizeof(zone_settlement_items) / sizeof(zone_settlement_items[0]);

const char* const zone_wilderness_items[] = { "FROSTVEIL GLACIER",
                                              "MOONLIT GROVE",
                                              "THE SCORCHED EXPANSE",
                                              "THE WHISPERING WOODS",
                                              "STARFALL CRATER" };
const int zone_wilderness_items_size =
  sizeof(zone_wilderness_items) / sizeof(zone_wilderness_items[0]);

const char* const zone_dungeon_items[] = { "VAULT OF FORGOTTEN KINGS",
                                           "OBSIDIAN SPIRE",
                                           "CAVERNS OF THE WYRM",
                                           "SUNKEN SANCTUM",
                                           "THE HOLLOW KEEP" };
const int zone_dungeon_items_size = sizeof(zone_dungeon_items) / sizeof(zone_dungeon_items[0]);

const char* const zone_mystical_items[] = { "THE SHATTERED ISLES",
                                            "THE LABYRINTH OF ECHOES",
                                            "MIRRORLAKE",
                                            "CHRONOS RUINS",
                                            "THE ARCANE NEXUS" };
const int zone_mystical_items_size = sizeof(zone_mystical_items) / sizeof(zone_mystical_items[0]);

const char* const zone_conflict_items[] = { "THE CRIMSON MARSH",
                                            "REDRIDGE BATTLEFIELD",
                                            "GRAVE OF GIANTS",
                                            "ASHEN FIELDS",
                                            "BROKEN BANNER FORT" };
const int zone_conflict_items_size = sizeof(zone_conflict_items) / sizeof(zone_conflict_items[0]);
