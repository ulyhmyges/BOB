/*
**  Filename : playerFile.c
**
**  Made by : HT
**
**  Description : a back up file of a player *.ptbob
*/

#include <stdio.h>
#include "playerFile.h"

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
int addPlayerFile(Player *player, char *playerfile){
    FILE *f = fopen(playerfile, "r+");
    if (f != NULL){
        int playerTotal = 0;
        fscanf(f, "{%d}\n", &playerTotal);
        printPlayer(*player, f);
        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", playerTotal + 1);
        fclose(f);
        return 1;
    }else{
        printf("Erreur à l'écriture/lecture du fichier %s\n", playerfile);
        return 0;
    }
}