#include "../inc/game_data.h"

// main menu data
const char* main_menu_items[] = { "NEW GAME", "CONTINUE", "QUIT" };
const int main_menu_items_size = sizeof(main_menu_items) / sizeof(main_menu_items[0]);

// town menu data
const char* town_menu_items[] = { "MAP", "QUEST", "SHOP" };
const int town_menu_items_size = sizeof(town_menu_items) / sizeof(town_menu_items[0]);

// map menu data
const char* map_menu_items[] = {"SETTLEMENTS", "WILDERNESS", "DUNGEONS", "MYSTICAL", "CONFLICT ZONES"};
const int map_menu_items_size = sizeof(map_menu_items) / sizeof(map_menu_items[0]);

// Settlements
const char *settlements[] = {
    "Windmere Village",
    "Ironhold",
    "Thornbridge",
    "Duskwatch",
    "Serpents Rest"
};

// Wilderness & Natural Locations
const char *wilderness[] = {
    "The Whispering Woods",
    "Frostveil Glacier",
    "The Scorched Expanse",
    "Starfall Crater",
    "Moonlit Grove"
};

// Dungeons & Ruins
const char *dungeons[] = {
    "The Hollow Keep",
    "Caverns of the Wyrm",
    "Sunken Sanctum",
    "Obsidian Spire",
    "Vault of Forgotten Kings"
};

// Mystical & Unique Places
const char *mystical[] = {
    "The Shattered Isles",
    "The Arcane Nexus",
    "Mirrorlake",
    "Chronos Ruins",
    "The Labyrinth of Echoes"
};

// Conflict Zones
const char *conflict_zones[] = {
    "Redridge Battlefield",
    "The Crimson Marsh",
    "Grave of Giants",
    "Broken Banner Fort",
    "Ashen Fields"
};


// hero data
const BaseHero hero_types[] = {
    { "Warrior", "Tank / Melee", 90, 8, 1.12f, 1.06f, 8, 1.08f, "Strong against Goblins, Bandits" },
    { "Ranger",
      "Ranged DPS",
      60,
      11,
      1.08f,
      1.12f,
      4,
      1.06f,
      "Effective vs Flying (Dragon) and Witch" },
    { "Mage",
      "AOE Spellcaster",
      50,
      14,
      1.05f,
      1.15f,
      3,
      1.04f,
      "Counters large mobs (Zombies, Skeletons)" },
    { "Cleric",
      "Healer / Support",
      65,
      6,
      1.10f,
      1.04f,
      6,
      1.07f,
      "Protects party, heals against Demon/Vampire damage" },
    { "Rogue",
      "Burst DPS / Stealth",
      55,
      13,
      1.07f,
      1.14f,
      3,
      1.05f,
      "Strong vs Witch, Bandit, soft targets" },
    { "Paladin",
      "Off-tank / Support",
      80,
      9,
      1.11f,
      1.08f,
      7,
      1.09f,
      "Balanced, with resistance to undead" },
    { "Berserker",
      "High-risk Melee DPS",
      70,
      12,
      1.10f,
      1.13f,
      5,
      1.06f,
      "Excels vs Trolls, Werewolves" },
    { "Necromancer",
      "Summoner / Debuff",
      50,
      10,
      1.06f,
      1.10f,
      3,
      1.04f,
      "Counters undead enemies, raises minions" },
    { "Druid",
      "Hybrid / Nature",
      65,
      9,
      1.10f,
      1.09f,
      5,
      1.07f,
      "Control spells, good against Dragons and Trolls" },
    { "Monk",
      "Agile Melee / Buffer",
      60,
      10,
      1.09f,
      1.10f,
      5,
      1.08f,
      "Counters Demons and Vampires, buffs allies" }
};
const int hero_types_size = sizeof(hero_types) / sizeof(hero_types[0]);

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
