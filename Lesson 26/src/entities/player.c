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
    newPlayer->previousLocation = malloc(sizeof(struct Location));
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
    int possibleX = level->user->currentLocation->position.x;
    int possibleY = level->user->currentLocation->position.y;

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

        default:
            break; // We stay in place (usually 'turn' will pass then)
    }

    if (canGoToPosition(possibleY, possibleX)) {
        // We store info about the previous position (which is the current one)
        level->user->previousLocation->position.y = level->user->currentLocation->position.y;
        level->user->previousLocation->position.x = level->user->currentLocation->position.x;
        level->user->previousLocation->displaySign = level->user->currentLocation->displaySign;

        // We switch the current position to the new one where we are allowed to go
        level->user->currentLocation->position.y = possibleY;
        level->user->currentLocation->position.x = possibleX;
        level->user->currentLocation->displaySign = unctrl(mvinch(possibleY, possibleX));
    } else if(isMonsterOnLocation(&level->locations[possibleY][possibleX], level->monsters) == TRUE) {
        combat(level->user, getMonsterAt(&level->locations[possibleY][possibleX], level->monsters), TRUE);
    } else {
        // When player 'stays' where he is then we have to move cursor 'back' to his current location
        move(level->user->currentLocation->position.y, level->user->currentLocation->position.x);
    }
}


void playerDraw(Player user)
{
    mvprintw(user.currentLocation->position.y, user.currentLocation->position.x, PLAYER_SIGN);
    move(user.currentLocation->position.y, user.currentLocation->position.x);
}
