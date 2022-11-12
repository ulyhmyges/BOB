#ifndef ROOMFILE_H

#define ROOMFILE_H
#include "roomList.h"

void writeRoomFile(RoomList roomList, char *fichier);
RoomList * readRoomFile(char *fichier);
Room * readRoom(FILE *f);
void addRoomFile(Room room, char *fichier);
void removeRoomFileById(int id, char *fichier);
void removeRoomFileByIndex(int index, char *fichier);
void showRoomFileById(int id, char *fichier);
#endif // ROOMFILE_H