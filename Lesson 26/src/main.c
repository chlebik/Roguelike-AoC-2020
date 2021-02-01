#include "rogue.h"
#include "screen.h"
#include "level.h"
#include "player.h"
#include "monster.h"


int handleInput(char keyPressed, Level *level);

int main()
{
    srand(time(NULL));

    screenSetup();
    Level *level = createLevel(DEFAULT_LEVEL_NUMBER, NUMBER_OF_ROOMS, NUMBER_OF_MONSTERS);

    /* Main game loop */
    char keyPressed = ' ';
    while(keyPressed != 'q') {
        handleInput(keyPressed, level);
        moveMonsters(level);

        printGameHub(level);
        drawLevel(level);
        keyPressed = getch();
    }

	endwin();

	return 0;
}

int handleInput(char keyPressed, Level *level)
{
    switch (keyPressed) {
        // show inventory
        case 'i':
        case 'I':
            printInventory(*level->user);
            playerDraw(*level->user);
            break;

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