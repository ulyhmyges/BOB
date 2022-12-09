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

void writeMonsterFile(MonsterList monsterList, char *fwd);
MonsterList * readMonsterFile(char *fwd);
int addMonsterFile(Monster *monster, char *fwd);
void removeMonsterFile(Monster *monster, char *fwd);
void removeMonsterFileByName(char *name, char *fwd);
void removeMonsterFileByIndex(int index, char *fwd);

#endif // MONSTERFILE_H