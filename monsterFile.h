#ifndef MONSTERFILE_H

#define MONSTERFILE_H
#include "monsterList.h"

void writeMonsterFile(MonsterList monsterList, char *fwd);
MonsterList * readMonsterFile(char *fwd);
int addMonsterFile(Monster *monster, char *fwd);
int removeMonsterFile(Monster *monster, char *fwd);
int removeMonsterFileByName(char *name, char *fwd);
int removeMonsterFileByIndex(int index, char *fwd);

#endif // MONSTERFILE_H