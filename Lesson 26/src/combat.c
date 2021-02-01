#include <rogue.h>
#include <combat.h>
#include <monster.h>


void combat(Player *player, Monster *monster, bool playerFirst) {
    if (playerFirst == TRUE) {
        monster->health -= player->attack;
        if (monster->health > 0) {
            player->health -= monster->attack;
        } else {
            killMonster(monster);
        }
    } else {
        player->health -= monster->attack;
        if (player->health > 0) {
            monster->health -= player->attack;
        }
    }
}