#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>


typedef struct Player {
    int xPosition;
    int yPosition;
    int health;
} Player;

enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};

int screenSetup(void);
int mapSetup(void);
int handleInput(char, Player* user);
int playerMove(Player* user, enum Direction dir);
int playerDraw(Player* user);
bool canGoToPosition(int y, int x);
Player *playerSetup(void);



int main()
{
    Player *user; // There is a warning here (-Wunused-but-set-variable) - that will be
    char keyPressed;

    screenSetup();
    mapSetup();
    user = playerSetup();

    /* Main game loop */
    while((keyPressed = getch()) != 'q') {
        handleInput(keyPressed, user);
    }

	endwin();

	return 0;
}


Player *playerSetup(void)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    playerDraw(newPlayer);

    return newPlayer;
}

int screenSetup(void)
{
    initscr();
    printw("Roguelike game!");
    noecho();
    refresh();

    return 0;
}

int mapSetup(void)
{
    int x = 13;
    int y = 13;
    mvprintw(y++, x, "---------");
    mvprintw(y++, x, "|.......|");
    mvprintw(y++, x, "|.......|");
    mvprintw(y++, x, "|.......|");
    mvprintw(y++, x, "|.......|");
    mvprintw(y, x,   "---------");

    x = 30;
    mvprintw(y++, x, "---------");
    mvprintw(y++, x, "|.......|");
    mvprintw(y++, x, "|.......|");
    mvprintw(y++, x, "|.......|");
    mvprintw(y++, x, "|.......|");
    mvprintw(y, x,   "---------");

    x = 13;
    y = 25;
    mvprintw(y++, x, "------------");
    mvprintw(y++, x, "|..........|");
    mvprintw(y++, x, "|..........|");
    mvprintw(y++, x, "|..........|");
    mvprintw(y++, x, "|..........|");
    mvprintw(y, x,   "------------");

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


int playerMove(Player *user, enum Direction direction)
{
     int possibleX = user->xPosition;
     int possibleY = user->yPosition;

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
    mvprintw(user->yPosition, user->xPosition, ".");

    if(canGoToPosition(possibleY, possibleX)) {
        user->yPosition = possibleY;
        user->xPosition = possibleX;
    }

    // We redraw the player no matter if the position changed or not
    playerDraw(user);

    return 0;
}


bool canGoToPosition(int y, int x)
{
    const int ALLOWED_LOCATIONS_SIZE = 1;   // Hard-coded to simplify iteration loop
    char allowedLocations[] = {'.'};
    char locationToCheck = mvinch(y, x);

    for(int i = 0; i < ALLOWED_LOCATIONS_SIZE; i++) {
        if(locationToCheck == allowedLocations[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

int playerDraw(Player* user)
{
    mvprintw(user->yPosition, user->xPosition, "@");
    move(user->yPosition, user->xPosition);

    return 0;
}