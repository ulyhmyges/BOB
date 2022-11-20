#ifndef PLAYERFILE_H

#define PLAYERFILE_H
#include "playerList.h"

PlayerList * readPlayerFile(char *playerfile);
void writePlayerFile(PlayerList playerList, char *playerfile);
int addPlayerFile(Player *player, char *playerfile);

#endif // PLAYERFILE_H