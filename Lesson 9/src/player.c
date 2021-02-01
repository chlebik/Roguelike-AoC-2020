#include <rogue.h>


Player *playerSetup(void)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerDraw(newPlayer);

    return newPlayer;
}


int playerMove(Player *user, enum Direction direction)
{
     int possibleX = user->position.x;
     int possibleY = user->position.y;

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

    // Cleanup of current position
    mvprintw(user->position.y, user->position.x, FLOOR_SIGN);

    if(canGoToPosition(possibleY, possibleX)) {
        user->position.y = possibleY;
        user->position.x = possibleX;
    }

    // We redraw the player no matter if the position changed or not
    playerDraw(user);

    return 0;
}


int playerDraw(Player *user)
{
    mvprintw(user->position.y, user->position.x, PLAYER_SIGN);
    move(user->position.y, user->position.x);

    return 0;
}
