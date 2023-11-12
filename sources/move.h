/*
**  Filename : run.h
**
**  Made by : HT
**
**  Description : functions about movement of character and monsters
*/

#ifndef MOVE_H

#define MOVE_H
#include "level.h"
#include "itemFile.h"
#include "fight.h"
#include "utils.h"

//#include <stdlib.h>

boolean isLock(Level *level, int h, int w);
int isWall(Level* level, int h, int w);
int isGap(Level* level, int h, int w);
int isSpike(Level* level, int h, int w);
int isHealth(Level* level, int h, int w);
int isRock(Level* level, int h, int w);
boolean isBoss(Level *level, int h, int w);
int isDoor(Level* level, int h, int w);
int isItem(Level* level, int h, int w);
int isBlank(Level* level, int h, int w);
int isSafe(Level *level, int h, int w);
boolean isPerson(Level* level, int h, int w);
boolean isMonster(Level* level, int h, int w);
boolean isEnd(Level* level, int h, int w);
boolean isNext(Level* level, int h, int w);

void showCurrentRoom(Level* level);

void movePerson(Level *level, char key);
void goToNextPoint(Level *level, int h, int w);
void reachCardinalPoint(Level* level);
void showEnd(void);

#endif // MOVE_H