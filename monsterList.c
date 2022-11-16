#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "monsterList.h"
#include "monster.h"

MonsterList *newMonsterList(void)
{
    MonsterList *monsterList = malloc(sizeof(MonsterList));
    monsterList->capacity = 35;
    monsterList->size = 0;
    monsterList->list = malloc(sizeof(Monster *) * monsterList->capacity);
    return monsterList;
}

void freeMonsterList(MonsterList *monsterList)
{
    for (int i = 0; i < monsterList->size; i += 1)
    {
        freeMonster(monsterList->list[i]);
    }
    free(monsterList->list);
    free(monsterList);
}

int addMonsterList(Monster *monster, MonsterList *monsterList)
{
    if (monsterList->size < monsterList->capacity)
    {
        monsterList->list[monsterList->size] = monster;
        monsterList->size += 1;
        return 1;
    }
    else
    {
        // augmenter la capacité de la liste !!
        return 0;
    }
}

int removeMonsterList(Monster *monster, MonsterList *monsterList)
{
    int i;
    for (i = 0; i < monsterList->size; i += 1)
    {
        if (monsterList->list[i] == monster)
        {
            freeMonster(monsterList->list[i]);
            monsterList->size -= 1;
            break;
        }
    }
    for (int j = i; j < monsterList->size; j += 1)
    {
        monsterList->list[j] = monsterList->list[j + 1];
    }
    if (i <= monsterList->size)
    {
        return 1;
    }
    return 0;
}

int removeMonsterListByName(char *name, MonsterList *monsterList)
{
    int i;
    for (i = 0; i < monsterList->size; i += 1)
    {
        if (!strcmp(monsterList->list[i]->name, name))
        {
            freeMonster(monsterList->list[i]);
            monsterList->size -= 1;
            break;
        }
    }
    for (int j = i; j < monsterList->size; j += 1)
    {
        monsterList->list[j] = monsterList->list[j + 1];
    }
    if (i <= monsterList->size)
    {
        return 1;
    }
    return 0;
}
int removeMonsterListByIndex(int index, MonsterList *monsterList)
{
    if (index >= 0 && index < monsterList->size)
    {
        freeMonster(monsterList->list[index]);
        monsterList->size -= 1;
        for (int j = index; j < monsterList->size; j += 1)
        {
            monsterList->list[j] = monsterList->list[j + 1];
        }
        return 1;
    }
    return 0;
}

void showMonsterList(MonsterList monsterList)
{
    printf("{%d}\n", monsterList.size);
    for (int i = 0; i < monsterList.size; i += 1)
    {
        showMonster(*monsterList.list[i]);
    }
}

void printMonsterList(MonsterList monsterList, FILE *f){
    fprintf(f, "{%d}\n", monsterList.size);
    for (int i = 0; i <monsterList.size; i += 1){
        printMonster(*monsterList.list[i], f);
    }
}