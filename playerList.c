#include <stdio.h>
#include <stdlib.h>
#include "playerList.h"

PlayerList * newPlayerList(){
    PlayerList *playerList = malloc(sizeof(PlayerList));
    playerList->size = 0;
    playerList->capacity = 35;
    playerList->list = malloc(sizeof(Player *) * playerList->capacity);
    return playerList;
}

void freePlayerList(PlayerList *playerList){
    for (int i = 0; i < playerList->size; i += 1){
        freePlayer(playerList->list[i]);
    }
    free(playerList->list);
    free(playerList);
}

PlayerList * readPlayerList(FILE *f){
    PlayerList *playerList = newPlayerList();
    fscanf(f, "{%d}\n", &playerList->size);
    for (int i = 0; i < playerList->size; i += 1){
        playerList->list[i] = readPlayer(f);
    }
    return playerList;
}

void printPlayerList(PlayerList playerList, FILE *f){
    fprintf(f, "{%d}\n", playerList.size);
    for (int i = 0; i < playerList.size; i += 1){
        printPlayer(*playerList.list[i], f);
    }
}