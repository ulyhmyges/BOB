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
//
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    Level *level = newLevel(1, 9, 15, "./ressources/file.rtbob", "./ressources/file.itbob", "./ressources/file.mtbob");

    /*
    char c;
    while(c != 'e')
    {
        while (!kbhit())
        {
            puts("tape a char");
        }
        c = fgetc(stdin);
        //printf("c: %c\n", c);
    }
    printf("\nYou pressed '%c'!\n", c);
    */

    //selection du joueur
    Player *player = selectPlayer("./ressources/backup.ptbob");

    //sauvegarde de la partie
    PlayerList *playerList = readPlayerFile("./ressources/backup.ptbob");
    if (playerList->size == 0)
    {
        playerList->list[playerList->size] = player;
        playerList->size += 1;
    }
    writePlayerFile(*playerList, "./ressources/backup.ptbob");
    return 0;
}