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

#endif // MOVE_H