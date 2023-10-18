/*
**  Filename : roomList.c
**
**  Made by : HT
**
**  Description : editor of a file full of rooms *.mtbob
*/

#include <stdio.h>
#include <stdlib.h>
#include "roomList.h"

RoomList *newRoomList(void)
{
    RoomList *roomList = malloc(sizeof(RoomList));
    roomList->capacity = 15;
    roomList->size = 0;
    roomList->list = malloc(sizeof(Room *) * roomList->capacity);
    return roomList;
}

void freeRoomList(RoomList *roomList)
{
    for (int i = 0; i < roomList->size; i += 1) {
        freeRoom(roomList->list[i]);
    }
    free(roomList->list);
    free(roomList);
}

int addRoom(RoomList *roomList, Room *room)
{
    if (roomList->size < roomList->capacity)
    {
        roomList->list[roomList->size] = room;
        roomList->size += 1;
        room->id = roomList->size;
        return 1;
    }
    return 0;
}

int updateList(RoomList *roomList, Room *room, int index)
{
    if (index >= 0 && index < roomList->size)
    {
        roomList->list[index] = room;
        return 1;
    }
    return 0;
}

int removeByRoom(RoomList *roomList, Room *room)
{
    int i = 0;
    while (roomList->list[i] != room && i < roomList->size)
    {
        i += 1;
    }

    if (i < roomList->size)
    {
        if (roomList->list[i] == room)
        {
            freeRoom(room);
            roomList->size -= 1;
            for (int j = i; j < roomList->size; j += 1)
            {
                roomList->list[j] = roomList->list[j + 1];
            }
            return 1;
        }
    }
    return 0;
}

int removeByIndex(RoomList *roomList, int index)
{
    if (index >= 0 && index < roomList->size)
    {
        freeRoom(roomList->list[index]);
        roomList->size -= 1;
        for (int i = index; i < roomList->size; i += 1)
        {
            roomList->list[i] = roomList->list[i + 1];
        }
        return 1;
    }
    return 0;
}

void showRoomList(RoomList roomList)
{
    printf("{%d}\n", roomList.size);
    for (int i = 0; i < roomList.size; i += 1)
    {
        showRoom(*roomList.list[i]);
    }
}

void printRoomList(RoomList roomList, FILE *f){
    fprintf(f, "{%d}\n", roomList.size);
    for (int i = 0; i < roomList.size; i += 1){
        printRoom(*roomList.list[i], f);
    }
}