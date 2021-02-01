#ifndef ITEM_H
#define ITEM_H

#include "level.h"
#include "weapon.h"

typedef enum {WEAPON_TYPE, POTION_TYPE} ItemType;

typedef struct Item {

    char name[32];
    ItemType type;
    Location location;

    union {
        Weapon *weapon;
    } item;

} Item;



Item *createSword(int attack, int endurance);

#endif
