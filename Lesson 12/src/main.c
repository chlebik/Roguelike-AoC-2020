#include "rogue.h"


int main()
{
    Player *user;
    char keyPressed;
    srand(time(NULL));

    screenSetup();
    roomsSetup(NUMBER_OF_ROOMS);
    Level * level = createLevel(DEFAULT_LEVEL_NUMBER, NUMBER_OF_ROOMS, NUMBER_OF_MONSTERS);
    user = playerSetup();

    /* Main game loop */
    while((keyPressed = getch()) != 'q') {
        handleInput(keyPressed, user);
    }

	endwin();

	return 0;
}

int handleInput(char keyPressed, Player *user)
{
    switch (keyPressed) {
        // move up
        case 'w':
        case 'W':
            playerMove(user, DIRECTION_N);
            break;

        // move left
        case 'a':
        case 'A':
            playerMove(user, DIRECTION_W);
            break;

        // move right
        case 'd':
        case 'D':
            playerMove(user, DIRECTION_E);
            break;

        // move down
        case 's':
        case 'S':
            playerMove(user, DIRECTION_S);
            break;

        default:
            break;
    }

    return 0;
}