#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "run.h"
#include "lowercase.h"
#include "player.h"
#include "playerFile.h"

Player * selectPlayer()
{
    puts("Welcome at BOB");
    puts("Choose your player:");
    puts("-> Briatte");
    puts("-> Chevaillier");
    puts("-> Hennou");
    char *name = malloc(sizeof(char) * 12);
    do
    {
        puts("Tape the name: ");
        scanf("%s", name);
        lowercase(name);
    } while (strcmp(name, "briatte") && strcmp(name, "chevaillier") && strcmp(name, "hennou"));
    puts("start");
    Player *player;
    PlayerList *playerList = readPlayerFile("player.ptbob");
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