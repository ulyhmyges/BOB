/*
**  Filename : monsterList.c
**
**  Made by : HT
**
**  Description : list of monsters' pointers
*/

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

/**
 * @brief add a new monster to the list based on value of monster
 *
 * @param monster
 * @param monsterList
 * @return int
 */
int addMonsterList(Monster *monster, MonsterList *monsterList)
{
    if (monsterList->size < monsterList->capacity)
    {
        monsterList->list[monsterList->size] = newMonster(
            monster->name,
            monster->hpMax,
            monster->dmg,
            monster->shoot,
            monster->ss,
            monster->flight);
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
/**
 * @brief Remove Monster by name from monsterList
 *
 * @param monsterList Object contains the list of monsters
 * @return 1 if succeed 0 otherwise
 */
int removeMonsterByName(MonsterList *monsterList)
{
    Monster *monster;
    monster = getMonsterByName(monsterList);
    if (monster == NULL)
    {
        printf("Monster not found\n");
        return 0;
    }
    showMonster(*monster);
    printf("Monster %s removed.\n", monster->name);
    if (removeMonster(monster, monsterList))
    {
        return 1;
    };
    return 0;
}

/**
 * @brief Get the Monster By Name from monsterList
 *
 * @param name
 * @param monsterList List od items
 * @return Monster*
 */
Monster *getMonsterByName(MonsterList *monsterList)
{
    char *name = malloc(sizeof(char) * 21);
    printf("Name of the monster?: ");
    fgets(name, 34, stdin);
    fgets(name, 34, stdin);
    sscanf(name, "%[^\n]", name);

    int i;
    for (i = 0; i < monsterList->size; i += 1)
    {
        if (!strcmp(monsterList->list[i]->name, name))
        {
            return monsterList->list[i];
        }
    }
    free(name);
    return NULL;
}

/**
 * @brief update a Monster object by its name from monsterList
 *
 * @param monsterList List of Monster objects
 * @return int 1 if succeed 0 otherwise
 */
int updateMonsterByName(MonsterList *monsterList)
{
    Monster *monster;
    monster = getMonsterByName(monsterList);
    if (monster == NULL)
    {
        printf("Monster not found\n");
        return 0;
    }
    showMonster(*monster);
    monster = askMonster(monster);
    showMonster(*monster);
    // freeMonster(monster);
    return 1;
}

/**
 * @brief supprime la première occurrence monster de la liste et retourne 1 en cas de succès et 0 sinon
 *
 * @param monster Monster object
 * @param monsterList List contains items of characters
 * @return int 1 if succeed
 */
int removeMonster(Monster *monster, MonsterList *monsterList)
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

void printMonsterList(MonsterList monsterList, FILE *f)
{
    fprintf(f, "{%d}\n", monsterList.size);
    for (int i = 0; i < monsterList.size; i += 1)
    {
        printMonster(*monsterList.list[i], f);
    }
}