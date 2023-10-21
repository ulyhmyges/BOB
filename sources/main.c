/*
**  Filename : main.c
**
**  Made by : HT
**
**  Description : this is the main file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "room.h"
#include "roomList.h"
#include "roomFile.h"
#include "item.h"
#include "itemList.h"
#include "itemFile.h"
#include "monster.h"
#include "monsterList.h"
#include "monsterFile.h"
#include "level.h"
#include "map.h"
#include "run.h"
#include "player.h"
#include "playerFile.h"
#include "move.h"

//

int main(int argc, char const *argv[])
{
    Level *level = newLevel(1, 9, 15,
                            "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.rtbob",
                            "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.itbob",
                            "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.mtbob");

    char c;
    while (1)
    {

        system("clear");
        system("echo '\e[032m'");
        showCurrentRoom(level);

        while (!kbhit())
        {
        }
        c = getchar();

        // printf("char: %c\n", c);
        fflush(stdin);
    }

    // // selection du joueur
    // Player *player = selectPlayer("./ressources/backup.ptbob");

    // // sauvegarde de la partie
    // PlayerList *playerList = readPlayerFile("./ressources/backup.ptbob");
    // if (playerList->size == 0)
    // {
    //     playerList->list[playerList->size] = player;
    //     playerList->size += 1;
    // }
    // writePlayerFile(*playerList, "./ressources/backup.ptbob");

    return 0;
}