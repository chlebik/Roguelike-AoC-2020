#include <rogue.h>
#include <player.h>
#include <room.h>
#include <monster.h>
#include <combat.h>
#include <item.h>


Player *playerSetup(void)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->currentLocation = malloc(sizeof(struct Location));
    newPlayer->items = malloc((sizeof (Item)) *  MAX_ITEMS);

    newPlayer->maxHealth = 20;
    newPlayer->health = 20;
    newPlayer->attack = 3;
    newPlayer->gold = 0;
    newPlayer->exp = 0;
    newPlayer->numberOfItems = 1;
    newPlayer->items[0] = createSword(1, 10);

    return newPlayer;
}


void playerMove(Level *level, enum Direction direction) {
    int possibleX = level->player->currentLocation->position.x;
    int possibleY = level->player->currentLocation->position.y;

    switch (direction) {
        // move up
        case DIRECTION_N:
            possibleY -= 1;
            break;

        // move left
        case DIRECTION_W:
            possibleX -= 1;
            break;

        // move right
        case DIRECTION_E:
            possibleX += 1;
            break;

        // move down
        case DIRECTION_S:
            possibleY += 1;
            break;

        // move NW
        case DIRECTION_NW:
            possibleY -= 1;
            possibleX -= 1;
            break;

        // move NE
        case DIRECTION_NE:
            possibleY -= 1;
            possibleX += 1;
            break;

        // move SE
        case DIRECTION_SE:
            possibleY += 1;
            possibleX += 1;
            break;

        // move SW
        case DIRECTION_SW:
            possibleY += 1;
            possibleX -= 1;
            break;

        default:
            break; // We stay in place (usually 'turn' will pass then)
    }

    if (canGoToLocation(level->locations[possibleY][possibleX], *level->player, level->monsters)) {
        level->player->currentLocation = &level->locations[possibleY][possibleX];
    } else if(isMonsterOnLocation(&level->locations[possibleY][possibleX], level->monsters) == TRUE) {
        combat(level->player, getMonsterAt(&level->locations[possibleY][possibleX], level->monsters), TRUE);
    } else {
        // When player 'stays' where he is then we have to move cursor 'back' to his current location
        move(level->player->currentLocation->position.y, level->player->currentLocation->position.x);
    }
}


void drawPlayer(Player user)
{
    mvprintw(user.currentLocation->position.y, user.currentLocation->position.x, PLAYER_SIGN);
    move(user.currentLocation->position.y, user.currentLocation->position.x);
}
