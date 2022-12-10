/*
**  Filename : playerFile.h
**
**  Made by : HT
**
**  Description : a back up file of a player *.ptbob
*/

#ifndef PLAYERFILE_H

#define PLAYERFILE_H
#include "playerList.h"

int addPlayerFile(Player *player, char *playerfile);
void writePlayerFile(PlayerList playerList, char *playerfile);
PlayerList *readPlayerFile(char *playerfile);

#endif // PLAYERFILE_H