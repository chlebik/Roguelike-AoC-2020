#include <rogue.h>
#include <level.h>
#include <player.h>


void screenSetup(void)
{
    initscr();
    noecho();
    refresh();
}

void printGameHub(Level *level)
{
    mvprintw(40, 0, "    Level: %d", level->levelNumber);
    printw("    Gold: %d", level->user->gold);
    printw("    Hp: %d(%d)", level->user->health, level->user->maxHealth);
    printw("    Attack: %d", level->user->attack);
    printw("    Exp: %d", level->user->exp);
    printw("      ");
}

void printInventory(Player player)
{
    mvprintw(41, 0, "    Inventory: ");

    for(int i = 0; i < player.numberOfItems; i++) {
        printw(player.items[i]->name);
    }

}