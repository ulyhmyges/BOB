/*
**  Filename : roomFile.h
**
**  Made by : HT
**
**  Description : editor of a file full of rooms *.rtbob
*/

#ifndef ROOMFILE_H

#define ROOMFILE_H
#include "roomList.h"
#include "stdlib.h"

void writeRoomFile(RoomList roomList, char *file);
RoomList * readRoomFile(char *roomfile, char *monsterfile);
Room * readRoom(FILE *f, char *monsterfile);
void addRoomFile(Room room, char *file);
void removeRoomFileById(int id, char *file, char *monsterfile);
void removeRoomFileByIndex(int index, char *file, char *monsterfile);
void showRoomFileById(int id, char *file, char *monsterfile);

#endif // ROOMFILE_H