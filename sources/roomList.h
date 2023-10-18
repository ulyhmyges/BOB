/*
**  Filename : roomList.h
**
**  Made by : HT
**
**  Description : list of rooms' pointers *.rtbob
*/

#ifndef ROOMLIST_H

#define ROOMLIST_H

#include "room.h"


typedef struct RoomList {
    Room **list;
    int size;
    int capacity;
} RoomList;

RoomList *newRoomList(void);
void freeRoomList(RoomList *roomList);
int addRoom(RoomList *roomList, Room *room);
int updateList(RoomList *roomList, Room *room, int index);
int removeByRoom(RoomList *roomList, Room *room);
int removeByIndex(RoomList *roomList, int index);
void showRoomList(RoomList roomList);
void printRoomList(RoomList roomList, FILE *f);
#endif // ROOMLIST_H
