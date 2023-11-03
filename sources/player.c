/*
**  Filename : player.c
**
**  Made by : HT
**
**  Description : model of a player (for example Hennou)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

Player *newPlayer(char *name, float hpMax, int shield, float dmg, boolean ps, boolean ss, boolean flight, int achieve)
{
    Player *player = malloc(sizeof(Player));
    player->name = malloc(sizeof(char) * 35);
    strcpy(player->name, name);
    player->hpMax = hpMax;
    player->shield = shield;
    player->dmg = dmg;
    player->ps = ps;
    player->ss = ss;
    player->flight = flight;
    player->achieve = achieve;
    player->invincible = true;
    player->item = newItem("Empty", 0, 0, 0, false, false, false);
    return player;
}

void freePlayer(Player *player)
{
    freeItem(player->item);
    free(player->name);
    free(player);
}

void statPlayer(Player *player)
{
    printf("\n%s\n", player->name);
    printf("hp: %.1f\n", player->hpMax);
    printf("shield: %d\n", player->shield);
    printf("dmg: %.2f\n", player->dmg);
    if (player->ps)
    {
        printf("ps: true\n");
    }
    if (player->ss)
    {
        printf("ss: true\n");
    }
    if (player->flight)
    {
        printf("flight: true\n");
    }
}

void showPlayer(Player player)
{
    printf("---\n");
    printf("name=%s\n", player.name);
    printf("achieve=%d\n", player.achieve);
    if (player.hpMax)
    {
        if (player.hpMax == (int)player.hpMax)
        {
            printf("hpMax=%d\n", (int)player.hpMax);
        }
        else
        {
            printf("hpMax=%.1f\n", player.hpMax);
        }
    }
    if (player.shield)
    {
        printf("shield=%d\n", player.shield);
    }
    if (player.dmg)
    {
        if (player.dmg == (int)player.dmg)
        {
            printf("dmg=%d\n", (int)player.dmg);
        }
        else
        {
            printf("dmg=%.2f\n", player.dmg);
        }
    }
    if (player.ps)
    {
        printf("ps=%s\n", "true");
    }
    if (player.ss)
    {
        printf("ss=%s\n", "true");
    }
    if (player.flight)
    {
        printf("flight=%s\n", "true");
    }
}

void printPlayer(Player player, FILE *f)
{
    // fprintf(f, "---\n");
    fputs("---\n", f);
    fprintf(f, "name=%s\n", player.name);
    fprintf(f, "achieve=%d\n", player.achieve);
    if (player.hpMax)
    {
        if (player.hpMax == (int)player.hpMax)
        {
            fprintf(f, "hpMax=%d\n", (int)player.hpMax);
        }
        else
        {
            fprintf(f, "hpMax=%.1f\n", player.hpMax);
        }
    }
    if (player.shield)
    {
        fprintf(f, "shield=%d\n", player.shield);
    }
    if (player.dmg)
    {
        if (player.dmg == (int)player.dmg)
        {
            fprintf(f, "dmg=%d\n", (int)player.dmg);
        }
        else
        {
            fprintf(f, "dmg=%.2f\n", player.dmg);
        }
    }
    if (player.ps)
    {
        fprintf(f, "ps=%s\n", "true");
    }
    if (player.ss)
    {
        fprintf(f, "ss=%s\n", "true");
    }
    if (player.flight)
    {
        fprintf(f, "flight=%s\n", "true");
    }
}

Player *readPlayer(FILE *f)
{
    Player *player = newPlayer("p", 0, 0, 0, false, false, false, 1);
    char binaire[5];
    char var[50];
    fgets(var, 50, f);
    if (!strcmp(var, "---\n"))
    {
        fgets(var, 30, f);
    }
    sscanf(var, "name=%[^\n]", player->name);
    fgets(var, 30, f);
    int i = sscanf(var, "achieve=%d\n", &player->achieve);
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "hpMax=%f\n", &player->hpMax); // succès = 1 et échec = 0
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "shield=%d\n", &player->shield);
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "dmg=%f\n", &player->dmg);
    if (i == 1)
    {

        fgets(var, 30, f);
    }
    i = sscanf(var, "ps=%s\n", binaire);
    if (i == 1)
    {
        player->ps = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "ss=%s\n", binaire);
    if (i == 1)
    {
        player->ss = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "flight=%s\n", binaire);
    if (i == 1)
    {
        player->flight = true;
        fgets(var, 30, f);
    }
    fseek(f, -4, SEEK_CUR);
    return player;
}