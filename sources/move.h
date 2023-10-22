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


typedef enum MOVE {
    UP = 'z',
    RIGHT = 'd',
    DOWN = 's',
    LEFT = 'q',
} MOVE;

void showCurrentRoom(Level* level);
void game(Level* level);
int kbhit(void);
void movePerson(Level *level, char key);
void updateCurrentRoom(Level *level, int h, int w);
void changeRoom(Level *level);

int isWall(Level* level, int h, int w);
int isGap(Level* level, int h, int w);
int isSpike(Level* level, int h, int w);
int isHealth(Level* level, int h, int w);
int isRock(Level* level, int h, int w);
int isBoss(Level* level, int h, int w);
int isDoor(Level* level, int h, int w);
int isItem(Level* level, int h, int w);

#endif // MOVE_H