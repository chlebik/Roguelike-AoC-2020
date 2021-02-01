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

    newPlayer->health = 20;

    playerDraw(newPlayer);

    return newPlayer;
}


int playerMove(Player *user, enum Direction direction)
{
    int possibleX = user->currentLocation->position.x;
    int possibleY = user->currentLocation->position.y;

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

    if(canGoToPosition(possibleY, possibleX)) {
        // Cleanup of current position
        mvprintw(user->currentLocation->position.y, user->currentLocation->position.x, user->currentLocation->displaySign);

        // We store info about the previous position (which is current one)
        user->previousLocation->position.y = user->currentLocation->position.y;
        user->previousLocation->position.x = user->currentLocation->position.x;
        user->previousLocation->displaySign = user->currentLocation->displaySign;

        // We switch the current position to the new one where we'll allow to go
        user->currentLocation->position.y = possibleY;
        user->currentLocation->position.x = possibleX;
        user->currentLocation->displaySign = unctrl(mvinch(possibleY, possibleX));

        // We redraw the player no matter if the position changed or not
        playerDraw(user);
    } else {
        // When player 'stays' where he is then we have to move cursor 'back' to his current location
        move(user->currentLocation->position.y, user->currentLocation->position.x);
    }

    return 0;
}


int playerDraw(Player *user)
{
    mvprintw(user->currentLocation->position.y, user->currentLocation->position.x, PLAYER_SIGN);
    move(user->currentLocation->position.y, user->currentLocation->position.x);
    return 0;
}
