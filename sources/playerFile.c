/*
**  Filename : playerFile.c
**
**  Made by : HT
**
**  Description : a back up file of a player *.ptbob
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playerFile.h"
#include "lowercase.h"

PlayerList *readPlayerFile(char *playerfile)
{
    FILE *f = fopen(playerfile, "r");

    if (f != NULL)
    {
        PlayerList *playerList = readPlayerList(f);
        fclose(f);
        return playerList;
    }
    else
    {
        printf("Erreur à la lecture du fichier %s\n", playerfile);
        return NULL;
    }
}

void writePlayerFile(PlayerList playerList, char *playerfile)
{
    FILE *f = fopen(playerfile, "w");
    if (f != NULL)
    {
        printPlayerList(playerList, f);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'écriture du fichier %s\n", playerfile);
    }
}

/**
 * @brief Add a player to the file playerfile
 *
 * @param player
 * @param playerfile path to the file
 * @return 1 if succeed
 */
int addPlayerFile(Player *player, char *playerfile)
{
    FILE *f = fopen(playerfile, "r+");
    if (f != NULL)
    {
        int playerTotal = 0;
        fscanf(f, "{%d}\n", &playerTotal);
        printPlayer(*player, f);
        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", playerTotal + 1);
        fclose(f);
        return 1;
    }
    else
    {
        printf("Erreur à l'écriture/lecture du fichier %s\n", playerfile);
        return 0;
    }
}

Player* selectPlayer(char *playerfile)
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
    } while (strcmp(name, "briatte") && strcmp(name, "b") && strcmp(name, "chevaillier") && strcmp(name, "hennou"));
    Player *player;
    PlayerList *playerList = readPlayerFile(playerfile);
    switch (name[0])
    {
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
    for (int i = 0; i < playerList->size; i += 1)
    {
        if (!strcmp(playerList->list[i]->name, player->name))
        {
            player = playerList->list[i];
        }
    }
    return player;
}