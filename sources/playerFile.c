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

        // initialize pathPlayerfile attribute
        for (int i = 0; i < playerList->size; i += 1)
        {
            strcpy(playerList->list[i]->pathPlayerfile, playerfile);
        }
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
        writePlayerList(playerList, f);
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
        writePlayer(*player, f);
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

void savePlayer(Player *player)
{
    PlayerList *playerList = readPlayerFile(player->pathPlayerfile);
    switch (player->name[0])
    {
    case 'B':
        if (playerList->size > 0)
        {
            if (player->dmg < 3.5)
            {
                player->dmg = 3.5;
            }
            if (player->hpMax < 3)
            {
                player->hpMax = 3;
            }
            playerList->list[0] = player;
        }
        break;

    case 'H':
        if (playerList->size > 1)
        {
            playerList->list[1] = player;
        }
        break;

    case 'C':
        if (playerList->size > 2)
        {
            playerList->list[2] = player;
        }
        break;

    default:
        break;
    }

    if (playerList->size == 1 && player->hennou)
    {
        Player *hennou = newPlayer("Hennou", 6, 0, 2, false, false, false, 0);
        
        playerList->list[1] = hennou;
        playerList->size += 1;
    }

    // write on the file playerfile
    writePlayerFile(*playerList, player->pathPlayerfile);
}

Player *selectPlayer(char *playerfile)
{
    PlayerList *playerList = readPlayerFile(playerfile);
    puts("Welcome at Bob's game");
    puts("Choose your player:");

    // display players from the playerfile
    for (int i = 0; i < playerList->size; i += 1)
    {
        printf("---> %s\n", playerList->list[i]->name);
    }

    char *name = malloc(sizeof(char) * 12);
    do
    {
        printf("Tape the name of your player: ");
        scanf("%s", name);
        lowercase(name);
    } while (strcmp(name, "briatte") && strcmp(name, "b") && strcmp(name, "chevaillier") && strcmp(name, "hennou"));

    Player *player;

    switch (name[0])
    {
    case 'b':
        // player = newPlayer("Briatte", 3, 0, 3.50, false, false, false, 1);
        player = playerList->list[0];
        break;
    case 'c':
        player = newPlayer("Chevaillier", 1, 8, 2.50, false, false, true, 1);
        break;

    case 'h':
        player = playerList->list[1];
        break;
    }

    return player;
}