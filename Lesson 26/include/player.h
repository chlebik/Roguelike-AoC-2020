#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include "item.h"

typedef struct Player {
    struct Location *currentLocation;
    struct Location *previousLocation;
    int health;
    int attack;
    int gold;
    int maxHealth;
    int exp;
    int numberOfItems;
    Item **items;
} Player;


Player *playerSetup(void);
void playerDraw(Player user);
void placePlayerInTheLevel(Level *level);
void playerMove(Level *level, enum Direction direction);

#endif
