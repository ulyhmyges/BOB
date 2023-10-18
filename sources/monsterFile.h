/*
**  Filename : monsterFile.h
**
**  Made by : HT
**
**  Description : editor of a file full of monsters *.mtbob
*/

#ifndef MONSTERFILE_H

#define MONSTERFILE_H
#include "monsterList.h"

void writeMonsterFile(MonsterList monsterList, char *monsterfile);
MonsterList * readMonsterFile(char *monsterfile);
int addMonsterFile(Monster *monster, char *monsterfile);

void createMonster(char* monsterfile);

#endif // MONSTERFILE_H