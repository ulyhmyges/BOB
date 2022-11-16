#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item *newItem(char *name, int hpMax, int shield, float dmg, boolean ps, boolean ss, boolean flight)
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
        printf("hpMax=%d\n", item.hpMax);
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
            printf("dmg=%.1f\n", item.dmg);
        }
    }
    if (item.ps)
    {
        printf("ps=%s\n", "true");
    }
    if (item.ss)
    {
        printf("ss=%s\n", "true");
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
        fprintf(f, "hpMax=%d\n", item.hpMax);
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
