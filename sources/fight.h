/*
**  Filename : fight.h
**
**  Made by : HT
**
**  Description : 
*/

#ifndef FIGHT_H
#define FIGHT_H



#include <string.h>
#include <unistd.h>
#include <time.h>

#include "level.h"
#include "move.h"


direction directionToTakeMonster(Level* level, Monster* m);
boolean directionTakenMonster(Level *level, Monster* m, direction cardinal);
void movedMonster(Level* level, Monster* m, int time);
void restlessMonsters(Level* level);

void sideAttack(Level* level, Monster* m);
void dmgPlayer(Level* level);
boolean isSideBySide(Level *level, Monster *m);

boolean canShoot(Level* level);
boolean isSpectral(Level* level);

// for the player
boolean isClear(Level* level, int h, int w);
boolean noObstacle(Level* level, int h, int w);
void dmgMonster(Level* level, int h, int w);

void upShoot(Level* level, int h, int w);
void upSS(Level* level, int h, int w);
void downShoot(Level* level, int h, int w);
void downSS(Level* level, int h, int w);
void leftShoot(Level* level, int h, int w);
void leftSS(Level* level, int h, int w);
void rightShoot(Level* level, int h, int w);
void rightSS(Level* level, int h, int w);
void shoot(Level *level, char letter);


void monsterShoot(Level* level, Monster *m, direction way);
void randomMovedMonster(Level* level, Monster *m);

// boss
void jaggerBossAttack(Level *level, Monster *m);
void LeninaBossAttack(Level *level, Monster *m);
void AthinaBossAttack(Level *level, Monster *m);
Monster *createBossJagger(void);
Monster *createBossLenina(void);
Monster *createBossAthina(void);
void addBossToRoom(Level* level, Room *room);
void cardinalShoot(Level* level, int h, int w);

#endif // FIGHT_H