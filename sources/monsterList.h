/*
**  Filename : monsterList.h
**
**  Made by : HT
**
**  Description : list of monsters' pointers
*/

#ifndef MONSTERLIST_H

#define MONSTERLIST_H
#include "monster.h"

typedef struct MonsterList {
    Monster **list;
    int size;
    int capacity;
} MonsterList;

MonsterList * newMonsterList(void);
void freeMonsterList(MonsterList *monsterList);
int addMonsterList(Monster *monster, MonsterList *monsterList);
int removeMonsterList(Monster *monster, MonsterList *monsterList);
int removeMonsterListByName(char *name, MonsterList *monsterList);
int removeMonsterListByIndex(int index, MonsterList *monsterList);
void showMonsterList(MonsterList monsterList);
void printMonsterList(MonsterList monsterList, FILE *f);

int removeMonsterByName(MonsterList* monsterList);
int removeMonster(Monster* monster, MonsterList* monsterList);

int updateMonsterByName(MonsterList* monsterList);
Monster* getMonsterByName(MonsterList* monsterList);


#endif // MONSTERLIST_H