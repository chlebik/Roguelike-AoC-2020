#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

typedef struct Player {
    int xPosition;
    int yPosition;
    int health;
} Player;


int screenSetup(void);
int mapSetup(void);
Player *playerSetup(void);

int main()
{
    Player *user; // There is a warning here (-Wunused-but-set-variable) - that will be
    char keyPressed;

    screenSetup();
    mapSetup();
    user = playerSetup();

    while((keyPressed = getch()) != 'q') {

    }

	endwin();

	return 0;
}


Player* playerSetup(void)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
    move(newPlayer->yPosition, newPlayer->xPosition);

    return newPlayer;
}

int screenSetup(void)
{
    initscr();
    printw("Hello world");
    noecho();
    refresh();

    return 0;
}

int mapSetup(void)
{
    int x = 13;
    int y = 13;
    mvprintw(y++, x, "---------");
    mvprintw(y++, x, "|-------|");
    mvprintw(y++, x, "|-------|");
    mvprintw(y++, x, "|-------|");
    mvprintw(y++, x, "|-------|");
    mvprintw(y, x,   "---------");

    x = 30;
    mvprintw(y++, x, "---------");
    mvprintw(y++, x, "|-------|");
    mvprintw(y++, x, "|-------|");
    mvprintw(y++, x, "|-------|");
    mvprintw(y++, x, "|-------|");
    mvprintw(y, x,   "---------");

    x = 13;
    y = 25;
    mvprintw(y++, x, "------------");
    mvprintw(y++, x, "|----------|");
    mvprintw(y++, x, "|----------|");
    mvprintw(y++, x, "|----------|");
    mvprintw(y++, x, "|----------|");
    mvprintw(y, x,   "------------");

    return 0;
}