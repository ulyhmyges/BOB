/*
**  Filename : run.h
**
**  Made by : HT
**
**  Description : attempt to start the bob's game
*/

#ifndef MOVE_H

#define MOVE_H
#include "level.h"
#include "item.h"
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

void showCurrentRoom(Level* level);

// start a game
void game(Level* level);

int kbhit(void);
void movePerson(Level *level, char key);
void goToNextPoint(Level *level, int h, int w);
void reachCardinalPoint(Level* level);

direction directionToTakeMonster(Level* level, Monster* m);
boolean directionTakenMonster(Level *level, Monster* m, direction cardinal);
void movedMonster(Level* level, Monster* m);
void restlessMonsters(Level* level);

#endif // MOVE_H