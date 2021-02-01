#ifndef WEAPON_H
#define WEAPON_H

typedef enum {SWORD_TYPE, SPEAR_TYPE} WeaponType;

typedef struct Weapon {
    WeaponType type;
    int attack;
    int endurance;
} Weapon;


#endif
