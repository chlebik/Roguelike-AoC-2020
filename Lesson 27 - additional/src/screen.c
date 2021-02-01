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
    printw("    Gold: %d", level->player->gold);
    printw("    Hp: %d(%d)", level->player->health, level->player->maxHealth);
    printw("    Attack: %d", level->player->attack);
    printw("    Exp: %d", level->player->exp);
    printw("      ");
}

void printInventory(Player player)
{
    mvprintw(41, 0, "    Inventory: ");

    for(int i = 0; i < player.numberOfItems; i++) {
        printw(player.items[i]->name);
    }

}