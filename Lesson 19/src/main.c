#include "rogue.h"


int main()
{
    srand(time(NULL));

    screenSetup();
    Level *level = createLevel(DEFAULT_LEVEL_NUMBER, NUMBER_OF_ROOMS, NUMBER_OF_MONSTERS);

    // Initial drawing when we enter the game
    printGameHub(level);
    playerDraw(level->user);

    /* Main game loop */
    char keyPressed;
    while((keyPressed = getch()) != 'q') {
        handleInput(keyPressed, level);
        moveMonsters(level);
        printGameHub(level);
        playerDraw(level->user);  // We redraw the player position after redrawing everything else
    }

	endwin();

	return 0;
}

int handleInput(char keyPressed, Level *level)
{
    switch (keyPressed) {
        // move up
        case 'w':
        case 'W':
            playerMove(level, DIRECTION_N);
            break;

        // move left
        case 'a':
        case 'A':
            playerMove(level, DIRECTION_W);
            break;

        // move right
        case 'd':
        case 'D':
            playerMove(level, DIRECTION_E);
            break;

        // move down
        case 's':
        case 'S':
            playerMove(level, DIRECTION_S);
            break;

        default:
            break;
    }

    return 0;
}