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

int isWall(Level* level, int h, int w);
int isGap(Level* level, int h, int w);
int isSpike(Level* level, int h, int w);
int isHealth(Level* level, int h, int w);
int isRock(Level* level, int h, int w);
int isBoss(Level* level, int h, int w);
int isDoor(Level* level, int h, int w);
int isItem(Level* level, int h, int w);
int isBlank(Level* level, int h, int w);
int isSafe(Level *level, int h, int w);
boolean isPerson(Level* level, int h, int w);
boolean isMonster(Level* level, int h, int w);

void showCurrentRoom(Level* level);

// start a game
void game(Level* level);

int kbhit(void);
void movePerson(Level *level, char key);
void goToNextPoint(Level *level, int h, int w);
void reachCardinalPoint(Level* level);

#endif // MOVE_H