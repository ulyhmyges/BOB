#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item *newItem(char *name, int hpMax, int shield, int dmg, boolean ps, boolean ss, boolean flight)
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
        printf("dmg=%d\n", item.dmg);
    }
    printf("ps=%s\n", item.ps ? "true" : "false");
    printf("ss=%s\n", item.ss ? "true" : "false");
    printf("flight=%s\n", item.flight ? "true" : "false");
}
