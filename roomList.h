#include "room.h"

#ifndef ROOMLIST_H

#define ROOMLIST_H

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
#endif // ROOMLIST_H
