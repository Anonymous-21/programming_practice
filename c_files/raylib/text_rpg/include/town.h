#ifndef TOWN_H
#define TOWN_H

#include "menu_item.h"

typedef struct TownMenu
{
    MenuItem *items;
    int selected;

}TownMenu;

void town_menu_init(TownMenu *town_menu);
void town_menu_draw(TownMenu *town_menu);
void town_menu_update(TownMenu *town_menu);

#endif // TOWN_H;