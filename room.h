#ifndef ROOM_H

#define ROOM_H

typedef struct Room {
    int id;
    int rows;
    int columns;
    char **map;
    //char objects[4];
    char rock;      //Un rocher infranchissable par le personnage et les monstres
    char gap;       //Un trou infranchissable par le personnage et les monstres
    char spike;     //Pic franchissable par le personnage et les monstres mais en prenant des dégâts
    char health;    //Objet généré aléatoirement (vie ou bouclier)
} Room;

Room * newRoom(void);
void showRoom(Room r);
void freeRoom(Room *r);
void updateRoom(Room *r, char thing, int row, int column);

// fonctions auxiliaires à la construction d'une pièce
void wallBorders(Room *r);
void putThing(Room *r, char thing, int pow, int row, int column, int verticalIncrement, int horizontalIncrement);
void designRoom1(Room *r);
void designRoom2(Room *r);
void designRoom3(Room *r);
void designRoom4(Room *r);
void designRoom5(Room *r);

#endif // ROOM_H