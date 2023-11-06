/*
**  Filename : fight.h
**
**  Made by : HT
**
**  Description : 
*/

#ifndef FIGHT_H
#define FIGHT_H
#include "level.h"
#include "move.h"
#include "string.h"


direction directionToTakeMonster(Level* level, Monster* m);
boolean directionTakenMonster(Level *level, Monster* m, direction cardinal);
void movedMonster(Level* level, Monster* m);
void restlessMonsters(Level* level);

void sideAttack(Level* level, Monster* m);
void dmgPlayer(Level* level);
boolean isSideBySide(Level *level, Monster *m);

#endif