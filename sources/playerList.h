/*
**  Filename : playerList.h
**
**  Made by : HT
**
**  Description : list of players' pointers
*/

#ifndef PLAYERLIST_H

#define PLAYERLIST_H
#include "player.h"

typedef struct PlayerList {
    Player **list;
    int size;
    int capacity;
} PlayerList;

PlayerList * newPlayerList();
void freePlayerList(PlayerList *playerList);

PlayerList * readPlayerList(FILE *f);
void printPlayerList(PlayerList PlayerList, FILE *f);

#endif // PLAYERLIST_H