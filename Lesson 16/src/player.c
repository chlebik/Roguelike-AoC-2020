#include <rogue.h>


Player *playerSetup(void)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->currentLocation = malloc(sizeof(struct Location));
    newPlayer->previousLocation = malloc(sizeof(struct Location));

    newPlayer->currentLocation->position.x = 14;
    newPlayer->currentLocation->position.y = 14;
    newPlayer->currentLocation->displaySign = FLOOR_SIGN;

    newPlayer->previousLocation->position.x = 14;
    newPlayer->previousLocation->position.y = 14;
    newPlayer->previousLocation->displaySign = FLOOR_SIGN;

    newPlayer->maxHealth = 20;
    newPlayer->health = 20;
    newPlayer->attack = 3;
    newPlayer->gold = 0;
    newPlayer->exp = 0;

    playerDraw(newPlayer);

    return newPlayer;
}


int playerMove(Level *level, enum Direction direction) {
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
        // Cleanup of current position
        mvprintw(level->user->currentLocation->position.y, level->user->currentLocation->position.x,
                 level->user->currentLocation->displaySign);

        // We store info about the previous position (which is current one)
        level->user->previousLocation->position.y = level->user->currentLocation->position.y;
        level->user->previousLocation->position.x = level->user->currentLocation->position.x;
        level->user->previousLocation->displaySign = level->user->currentLocation->displaySign;

        // We switch the current position to the new one where we'll allow to go
        level->user->currentLocation->position.y = possibleY;
        level->user->currentLocation->position.x = possibleX;
        level->user->currentLocation->displaySign = unctrl(mvinch(possibleY, possibleX));

        // We redraw the player no matter if the position changed or not
        playerDraw(level->user);
    } else if(isMonsterOnLocation(&level->locations[possibleY][possibleX], level->monsters) == TRUE) {
        combat(level->user, getMonsterAt(&level->locations[possibleY][possibleX], level->monsters), TRUE);
    } else {
        // When player 'stays' where he is then we have to move cursor 'back' to his current location
        move(level->user->currentLocation->position.y, level->user->currentLocation->position.x);
    }

    return 0;
}


int playerDraw(Player *user)
{
    mvprintw(user->currentLocation->position.y, user->currentLocation->position.x, PLAYER_SIGN);
    move(user->currentLocation->position.y, user->currentLocation->position.x);
    return 0;
}
