#ifndef ROOM_H

#define ROOM_H

typedef struct Room {
    int id;
    int rows;
    int columns;
    char **map;
} Room;

Room * newRoom(void);
void freeRoom(Room *r);
void wallBorders(Room *r);
void setThing(Room *r, char thing, int row, int column);
void showRoom(Room r);

#endif // ROOM_H