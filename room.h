#ifndef ROOM_H

#define ROOM_H

typedef struct Room {
    int id;
    int rows;
    int columns;
    char **map;
    char objects[4];
} Room;

Room * newRoom(void);
void freeRoom(Room *r);
void wallBorders(Room *r);
void showRoom(Room r);
void setThing(Room *r, char thing, int row, int column);
void putThing(Room *r, char thing, int pow, int row, int column);

#endif // ROOM_H