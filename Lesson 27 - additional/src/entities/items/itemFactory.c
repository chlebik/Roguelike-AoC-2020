#include "rogue.h"
#include "item.h"

Item *createSword(int attack, int endurance)
{
    Item *item = malloc(sizeof(Item));
    item->type = WEAPON_TYPE;
    strcpy(item->name, "Sword");

    Weapon *weapon = malloc(sizeof(Weapon));
    weapon->attack = attack;
    weapon->endurance = endurance;
    weapon->type = SWORD_TYPE;

    item->item.weapon = weapon;

    return item;
}
