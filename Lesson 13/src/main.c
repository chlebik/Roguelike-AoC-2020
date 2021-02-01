#include "rogue.h"


int main()
{
    srand(time(NULL));

    screenSetup();
    Level *level = createLevel(DEFAULT_LEVEL_NUMBER, NUMBER_OF_ROOMS, NUMBER_OF_MONSTERS);

    /* Main game loop */
    char keyPressed;
    while((keyPressed = getch()) != 'q') {
        handleInput(keyPressed, level->user);
        moveMonsters(level);
        playerDraw(level->user);  // We redraw the player position after redrawing everything else
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