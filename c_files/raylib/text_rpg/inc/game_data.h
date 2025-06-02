#ifndef GAME_DATA_H
#define GAME_DATA_H

typedef enum ShopType
{
    SHOP_TYPE_CONSUMABLES = 0,
    SHOP_TYPE_WEAPONS = 1,
    SHOP_TYPE_ARMORS = 2,
    SHOP_TYPE_ACCESSORIES = 3,

    SHOP_INVALID = -1,

} ShopType;

typedef enum MapZone
{
    MAP_ZONE_SETTLEMENTS = 0,
    MAP_ZONE_WILDERNESS = 1,
    MAP_ZONE_DUNGEONS = 2,
    MAP_ZONE_MYSTICAL = 3,
    MAP_ZONE_CONFLICT = 4,

    MAP_ZONE_INVALIED = -1,

} MapZone;

// town menu data
extern const char* const town_menu_items[];
extern const int town_menu_items_size;

// map menu data
extern const char* const map_menu_items[];
extern const int map_menu_items_size;

extern const char* const zone_settlement_items[];
extern const int zone_settlement_items_size;

extern const char* const zone_wilderness_items[];
extern const int zone_wilderness_items_size;

extern const char* const zone_dungeon_items[];
extern const int zone_dungeon_items_size;

extern const char* const zone_mystical_items[];
extern const int zone_mystical_items_size;

extern const char* const zone_conflict_items[];
extern const int zone_conflict_items_size;

// shop menu data
extern const char* const shop_menu_items[];
extern const int shop_menu_items_size;

// quests menu data
extern char* quest_menu_items[];
extern int quest_menu_items_size;

// enemy data
typedef struct BaseEnemy
{
    const char* const type;
    const float health;
    const float damage;
    const float defense;
    const float health_growth;
    const float damage_growth;
    const float defense_growth;

} BaseEnemy;

extern const BaseEnemy enemy_types[];
extern const int enemy_types_size;

#endif // GAME_DATA_H;