/*
**  Filename : item.c
**
**  Made by : HT
**
**  Description : model of a item
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "lowercase.h"

Item* newItem(char *name, float hpMax, int shield, float dmg, boolean ps, boolean ss, boolean flight)
{
    Item *item = malloc(sizeof(Item));
    item->name = malloc(sizeof(char) * 35);
    strcpy(item->name, name);
    item->hpMax = hpMax;
    item->shield = shield;
    item->dmg = dmg;
    item->ps = ps;
    item->ss = ss;
    item->flight = flight;
    return item;
}

void freeItem(Item *item)
{
    free(item->name);
    free(item);
}

/**
 * @brief affiche l'item avec ses attributs
 *
 * @param item un objet personnage
 */
void showItem(Item item)
{
    printf("---\n");
    printf("name=%s\n", item.name);
    if (item.hpMax)
    {
        if (item.hpMax == (int)item.hpMax)
        {
            printf("hpMax=%d\n", (int)item.hpMax);
        }
        else
        {
            printf("hpMax=%.1f\n", item.hpMax);
        }
    }
    if (item.shield)
    {
        printf("shield=%d\n", item.shield);
    }
    if (item.dmg)
    {
        if (item.dmg == (int)item.dmg)
        {
            printf("dmg=%d\n", (int)item.dmg);
        }
        else
        {
            printf("dmg=%.1f\n",item.dmg);
        }
    }
    if (item.ps)
    {
        printf("ps=%s\n","true");
    }
    if (item.ss)
    {
        printf("ss=%s\n","true");
    }
    if (item.flight)
    {
        printf("flight=%s\n", "true");
    }
}

/**
 * @brief écrit le contenu de l'item dans le fichier correspondant au pointeur f
 *
 * @param item un objet personnage
 * @param f pointeur FILE à l'état d'écriture
 */
void printItem(Item item, FILE *f)
{
    fputs("---\n", f);
    fprintf(f, "name=%s\n", item.name);
    if (item.hpMax)
    {
        if (item.hpMax == (int)item.hpMax)
        {
            fprintf(f, "hpMax=%d\n", (int)item.hpMax);
        }
        else
        {
            fprintf(f, "hpMax=%.1f\n", item.hpMax);
        }
    }
    if (item.shield)
    {
        fprintf(f, "shield=%d\n", item.shield);
    }
    if (item.dmg)
    {
        if (item.dmg == (int)item.dmg)
        {
            fprintf(f, "dmg=%d\n", (int)item.dmg);
        }
        else
        {
            fprintf(f, "dmg=%.1f\n", item.dmg);
        }
    }
    if (item.ps)
    {
        fprintf(f, "ps=%s\n", "true");
    }
    if (item.ss)
    {
        fprintf(f, "ss=%s\n", "true");
    }
    if (item.flight)
    {
        fprintf(f, "flight=%s\n", "true");
    }
}

Item *readItem(FILE *f)
{
    Item *item = newItem("a", 0, 0, 0, false, false, false);
    char binaire[5];
    char var[50];
    fgets(var, 50, f);
    if (!strcmp(var, "---\n"))
    {
        fgets(var, 30, f);
    }
    sscanf(var, "name=%[^\n]", item->name);
    fgets(var, 30, f);
    int i = sscanf(var, "hpMax=%f\n", &item->hpMax); // succès = 1 et échec = 0
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "shield=%d\n", &item->shield);
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "dmg=%f\n", &item->dmg);
    if (i == 1)
    {

        fgets(var, 30, f);
    }
    i = sscanf(var, "ps=%s\n", binaire);
    if (i == 1)
    {
        item->ps = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "ss=%s\n", binaire);
    if (i == 1)
    {
        item->ss = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "flight=%s\n", binaire);
    if (i == 1)
    {
        item->flight = true;
        fgets(var, 30, f);
    }
    fseek(f, -4, SEEK_CUR);
    return item;
}

Item* askItem(Item* item)
{
    if (item == NULL){
        item = newItem("a", 0, 0, 0, false, false, false);
    }
    printf("name = ");
    scanf("%s", item->name);
    printf("hpMax = ");
    scanf("%f", &item->hpMax);
    printf("shield = ");
    scanf("%i", &item->shield);
    printf("dmg = ");
    scanf("%f", &item->dmg);

    char *boole = malloc(sizeof(char) * 5);

    printf("ps = ");
    do
    {
        printf("true or false? ");
        scanf("%s", boole);
        lowercase(boole);
    } while (strcmp(boole, "true") && strcmp(boole, "false"));
    item->ps = true;
    if (strcmp(boole, "true")) {
        item->ps = false;
    }

    printf("ss = ");
    do
    {
        printf("true or false? ");
        scanf("%s", boole);
        lowercase(boole);
    } while (strcmp(boole, "true") && strcmp(boole, "false"));
    item->ss = true;
    if (strcmp(boole, "true")) {
        item->ss = false;
    }

    printf("flight = ");
    do
    {
        printf("true or false? ");
        scanf("%s", boole);
        lowercase(boole);
    } while (strcmp(boole, "true") && strcmp(boole, "false"));
    item->flight = true;
    if (strcmp(boole, "true")) {
        item->flight = false;
    }

    return item;
}