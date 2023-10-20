/*
**  Filename : monster.c
**
**  Made by : HT
**
**  Description : model of a monster
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monster.h"
#include "item.h"
#include "lowercase.h"

Monster *newMonster(char *name, float hpMax, float dmg, boolean shoot, boolean ss, boolean flight)
{
    Monster *monster = malloc(sizeof(Monster));
    monster->name = malloc(sizeof(char) * 35);
    strcpy(monster->name, name);
    monster->hpMax = hpMax;
    monster->dmg = dmg;
    monster->shoot = shoot;
    monster->ss = ss;
    monster->flight = flight;
    return monster;
}

void freeMonster(Monster *monster)
{
    free(monster->name);
    free(monster);
}

void showMonster(Monster monster)
{
    printf("---\n");
    printf("name=%s\n", monster.name);
    if (monster.hpMax)
    {
        if (monster.hpMax == (int)monster.hpMax)
        {
            printf("hpMax=%d\n", (int)monster.hpMax);
        }
        else
        {
            printf("hpMax=%.1f\n", monster.hpMax);
        }
    }
    if (monster.shoot)
    {
        printf("shoot=%s\n", "true");
    }
    if (monster.ss)
    {
        printf("ss=%s\n", "true");
    }
    if (monster.flight)
    {
        printf("flight=%s\n", "true");
    }
}

void printMonster(Monster monster, FILE *f)
{
    fprintf(f, "---\n");
    fprintf(f, "name=%s\n", monster.name);
    if (monster.hpMax)
    {
        if (monster.hpMax == (int)monster.hpMax)
        {
            fprintf(f, "hpMax=%d\n", (int)monster.hpMax);
        }
        else
        {
            fprintf(f, "hpMax=%.1f\n", monster.hpMax);
        }
    }
    if (monster.shoot){
        fprintf(f, "shoot=%s\n", "true");
    }
    if (monster.ss){
        fprintf(f, "ss=%s\n", "true");
    }
    if (monster.flight){
        fprintf(f, "flight=%s\n", "true");
    }
}

Monster *readMonster(FILE *f){
    Monster *monster = newMonster("m", 0, -1, false, false, false);
    char binaire[5];
    char var[50];
    fgets(var, 50, f);
    if (!strcmp(var, "---\n"))
    {
        fgets(var, 30, f);
    }
    sscanf(var, "name=%[^\n]", monster->name);
    fgets(var, 30, f);
    int i = sscanf(var, "hpMax=%f\n", &monster->hpMax); // succès = 1 et échec = 0
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "shoot=%s\n", binaire);
    if (i == 1)
    {
        monster->shoot = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "ss=%s\n", binaire);
    if (i == 1)
    {
        monster->ss = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "flight=%s\n", binaire);
    if (i == 1)
    {
        monster->flight = true;
        fgets(var, 30, f);
    }
    fseek(f, -4, SEEK_CUR);
    return monster;
}


Monster* askMonster(Monster* monster)
{
    if (monster == NULL){
        monster = newMonster("m", 0, -1, false, false, false);
    }

    // name
    printf("name = ");
    if (fgets(monster->name, 34, stdin) == NULL){
        fgets(monster->name, 34, stdin);
    }
    
    sscanf(monster->name, "%[^\n]", monster->name);

    // hpMax
    printf("hpMax = ");
    scanf("%f", &monster->hpMax);

    char *boole = malloc(sizeof(char) * 5);

    // shoot
    printf("shoot = ");
    do
    {
        printf("true or false? ");
        scanf("%s", boole);
        lowercase(boole);
    } while (strcmp(boole, "true") && strcmp(boole, "false"));
    monster->shoot = true;
    if (strcmp(boole, "true")) {
        monster->shoot = false;
    }

    // ss
    printf("ss = ");
    do
    {
        printf("true or false? ");
        scanf("%s", boole);
        lowercase(boole);
    } while (strcmp(boole, "true") && strcmp(boole, "false"));
    monster->ss = true;
    if (strcmp(boole, "true")) {
        monster->ss = false;
    }

    // flight
    printf("flight = ");
    do
    {
        printf("true or false? ");
        scanf("%s", boole);
        lowercase(boole);
    } while (strcmp(boole, "true") && strcmp(boole, "false"));
    monster->flight = true;
    if (strcmp(boole, "true")) {
        monster->flight = false;
    }

    return monster;
}