/*
**  Filename : run.h
**
**  Made by : HT
**
**  Description : attempt to start the bob's game
*/

#ifndef RUN_H

#define RUN_H

#include "level.h"
#include "utils.h"
#include "move.h"
#include "lowercase.h"
#include "playerFile.h"



void crudItem(void);
void crudMonster(void);

// start a game
void newGame();
void game(Level* level);
Level* endOrNextLevel(Level* level);
#endif // RUN_H