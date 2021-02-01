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
            printInventory(*level->player);
            drawPlayer(*level->player);
            break;

        // move up
        case '8':
            playerMove(level, DIRECTION_N);
            break;

        // move left
        case '4':
            playerMove(level, DIRECTION_W);
            break;

        // move right
        case '6':
            playerMove(level, DIRECTION_E);
            break;

        // move down
        case '2':
            playerMove(level, DIRECTION_S);
            break;

        // move NW
        case '7':
            playerMove(level, DIRECTION_NW);
            break;

        // move NE
        case '9':
            playerMove(level, DIRECTION_NE);
            break;

        // move SW
        case '1':
            playerMove(level, DIRECTION_SW);
            break;

        // move SE
        case '3':
            playerMove(level, DIRECTION_SE);
            break;


        default:
            break;
    }

    return 0;
}