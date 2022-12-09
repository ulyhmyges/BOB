/*
**  Filename : run.c
**
**  Made by : HT
**
**  Description : attempt to start the bob's game
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "run.h"
#include "lowercase.h"
#include "player.h"
#include "playerFile.h"

Player * selectPlayer(char *playerfile)
{
    puts("Welcome at Bob's game");
    puts("Choose your player:");
    puts("-> Briatte");
    puts("-> Chevaillier");
    puts("-> Hennou");
    char *name = malloc(sizeof(char) * 12);
    do
    {
        printf("Tape the name of your player: ");
        scanf("%s", name);
        lowercase(name);
    } while (strcmp(name, "briatte") && strcmp(name, "chevaillier") && strcmp(name, "hennou"));
    puts("start...");
    Player *player;
    PlayerList *playerList = readPlayerFile(playerfile);
    switch (name[0]){
        case 'b':
            player = newPlayer("Briatte", 3, 0, 3.50, false, false, false, 1);
            break;
        case 'c':
            player = newPlayer("Chevaillier", 1, 8, 2.50, false, false, true, 1);
            break;
        
        case 'h':
            player = newPlayer("Hennou", 6, 0, 2, false, false, false, 1);
            break;
    }
    for (int i = 0; i < playerList->size; i += 1){
        if (!strcmp(playerList->list[i]->name, player->name)){
            player = playerList->list[i];
        }
    } 
    return player;
}