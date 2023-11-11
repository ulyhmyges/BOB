/*
**  Filename : level.c
**
**  Made by : HT
**
**  Description : model of a level of the bob's game
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "level.h"
#include "fight.h"

/**
 * @brief Create a Special Room object:
 * a ItemRoom/ItemRoomBonus (I)
 * or a Spawner (P)
 * or a BossRoom (B)
 *
 * @param rows
 * @param columns
 * @param kind I, P or B
 * @return Room*
 */
Room *createSpecialRoom(Level* level, int rows, int columns, char kind, char *itemfile, char *monsterfile)
{
    Room *r = NULL;
    ItemList *itemList = readItemFile(itemfile);
    int itemIndex = rand() % itemList->size;

    switch (kind)
    {
    case 'B': // boss room
        r = newRoom(rows, columns, "Boss", 3, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind; // le boss (M) au milieu de la pièce
        addBossToRoom(level, r);
        break;

    case 'I': // item room et item room bonus
        r = newRoom(rows, columns, "Item", 0, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind; // l'item (I) au milieu de la pièce
        r->item = itemList->list[itemIndex];
        break;

    default:
        r = newRoom(rows, columns, "Spawner", 0, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind; // le player (P) au milieu de la pièce
    }
    return r;
}
/**
 * @brief Procédure
 * création de la grille vide représentant l'ensemble des rooms de l'étage (floor)
 * création de la map de l'étage
 *
 * @param level
 */
void createFloor(Level *level, char *monsterfile)
{
    level->floor = malloc(sizeof(Room *) * level->height);
    for (int i = 0; i < level->height; i += 1)
    {
        level->floor[i] = malloc(sizeof(Room) * level->width);
    }
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            level->floor[i][j] = *newRoom(level->rows, level->columns, "Wall", 6, monsterfile);
        }
    }
    // création de la map vide
    level->map = newMap(level->height, level->width); // car level->height = 7 et level->width = 7
}

Level *newLevel(int id, int rows, int columns, char *roomfile, char *itemfile, char *monsterfile, Player *player)
{
    srand(time(NULL));
    Level *level = malloc(sizeof(Level));
    level->id = id; // niveau de l'étage
    level->height = 7;
    level->width = 7;
    level->rows = rows;       // for a room
    level->columns = columns; // for a room
    level->pathRoomfile = malloc(sizeof(char) * 99);
    strcpy(level->pathRoomfile, roomfile);
    level->pathItemfile = malloc(sizeof(char) * 99);
    strcpy(level->pathItemfile, itemfile);
    level->pathMonsterfile = malloc(sizeof(char) * 99);
    strcpy(level->pathMonsterfile, monsterfile);

    // création de la grille de rooms de type 'Wall' représentant l'étage + newMap()
    createFloor(level, monsterfile);

    // création special rooms
    level->spawner = createSpecialRoom(level, level->rows, level->columns, 'P', itemfile, monsterfile);
    level->bossRoom = createSpecialRoom(level, level->rows, level->columns, 'B', itemfile, monsterfile);
    level->itemRoom = createSpecialRoom(level, level->rows, level->columns, 'I', itemfile, monsterfile);
    level->itemRoomBonus = createSpecialRoom(level, level->rows, level->columns, 'I', itemfile, monsterfile);

    // représentation du personnage dans la pièce
    level->character = 'P';

    // add a player
    level->player = player;

    // direction par défaut
    level->direction = North;

    // place le spawner au centre de l'étage
    level->coord.u = level->height / 2;
    level->coord.v = level->width / 2;

    // position centrale du personnage dans la pièce
    level->coord.p.h = level->rows / 2;
    level->coord.p.w = level->columns / 2;

    // ajout de la room spawner au centre du tableau floor
    addRoomToFloor(level, level->coord.u, level->coord.v, level->spawner); // u,v = 3, 3
    updateMapLevel(level, level->coord.u, level->coord.v, level->map->spawn);

    // save spawner coordinates
    level->spawner->spot.u = level->coord.u;
    level->spawner->spot.v = level->coord.v;

    // pièce actuelle du personnage 'P'
    level->currentRoom = level->spawner;

    randFloor(level, roomfile, monsterfile); // placement aléatoire des pièces à partir du Spawner + bossRoom + itemRoomBonus

    // ajout de itemRoom (I)
    addItemRoom(level, level->itemRoom);

    // put cardinal doors for all kind of room and save them
    putAllDoors(level);
    saveCardinalDoors(level);

    // hidden Bonus room
    hideBonusRoom(level);

    // start to Spawner room
    level->coord.u = level->spawner->spot.u;
    level->coord.v = level->spawner->spot.v;

    // récupère la bonne configuration des rooms après le placement des portes
    *level->spawner = level->floor[level->coord.u][level->coord.v];
    *level->bossRoom = level->floor[level->bossRoom->spot.u][level->bossRoom->spot.v];
    *level->itemRoom = level->floor[level->itemRoom->spot.u][level->itemRoom->spot.v];
    *level->itemRoomBonus = level->floor[level->itemRoomBonus->spot.u][level->itemRoomBonus->spot.v];

    return level;
}

void randFloor(Level *level, char *roomfile, char *monsterfile)
{
    // create a list of rooms occupied by monsters ( < 7 for each room )
    RoomList *roomList = readRoomFile(roomfile, monsterfile);

    int count = 0;
    while (count < 10)
    {

        int index = 0; // index de la roomList
        // start with 'S' in the middle of floor
        level->coord.u = level->height / 2; // vertical coordinate
        level->coord.v = level->width / 2;  // horizontal coordinate
        int times = 0;
        while (count < 10 && times < 20)
        {
            level->direction = rand() % 4;
            int design = rand() % 5;
            design += 1;
            switch (level->direction)
            {
            case North:
                if (level->coord.u > 0 && level->map->grid[level->coord.u - 1][level->coord.v] == level->map->wall)
                {
                    level->coord.u -= 1;
                    count += 1;
                    break;
                }

            case East:
                if (level->coord.v < level->width - 1 && level->map->grid[level->coord.u][level->coord.v + 1] == level->map->wall)
                {
                    level->coord.v += 1;
                    count += 1;
                    break;
                }

            case South:
                if (level->coord.u < level->height - 1 && level->map->grid[level->coord.u + 1][level->coord.v] == level->map->wall)
                {
                    level->coord.u += 1;
                    count += 1;
                    break;
                }

            case West:
                if (level->coord.v > 0 && level->map->grid[level->coord.u][level->coord.v - 1] == level->map->wall)
                {
                    level->coord.v -= 1;
                    count += 1;
                    break;
                }

            // nothing happen
            case Center:
                break;
            }

            // création aléatoire d'une room à partir des rooms du fichier roomfile
            Room *room = roomList->list[index];

            // ajout de la room (et non le pointeur) dans la grille level->floor
            addRoomToFloor(level, level->coord.u, level->coord.v, room);

            // ajout des monstres dans la pièce
            addMonstersToRoom(level, level->coord.u, level->coord.v, monsterfile);

            // spécifie que la pièce est une room 'r' dans la map du Level struct
            updateMapLevel(level, level->coord.u, level->coord.v, 'r');

            times += 1;
            index = rand() % roomList->size;
        }
    }
    addBossRoom(level);
    // add Bonus item room (J) next to Boss room
    putItemRoom(level, level->coord.u, level->coord.v, level->itemRoomBonus);
    strcpy(level->itemRoomBonus->type, "Bonus");
    updateMapLevel(level, level->coord.u, level->coord.v, level->map->bonus);
}

int addBossRoom(Level *level)
{
    if (level->coord.u > 0 && level->map->grid[level->coord.u - 1][level->coord.v] == '0')
    {
        level->coord.u -= 1;
        addRoomToFloor(level, level->coord.u, level->coord.v, level->bossRoom);
        updateMapLevel(level, level->coord.u, level->coord.v, level->map->boss);
        return 1;
    }
    if (level->coord.v < level->width - 1 && level->map->grid[level->coord.u][level->coord.v + 1] == '0')
    {
        level->coord.v += 1;
        addRoomToFloor(level, level->coord.u, level->coord.v, level->bossRoom);
        updateMapLevel(level, level->coord.u, level->coord.v, level->map->boss);
        return 1;
    }
    if (level->coord.u < level->height - 1 && level->map->grid[level->coord.u + 1][level->coord.v] == '0')
    {
        level->coord.u += 1;
        addRoomToFloor(level, level->coord.u, level->coord.v, level->bossRoom);
        updateMapLevel(level, level->coord.u, level->coord.v, level->map->boss);
        return 1;
    }
    if (level->coord.v > 0 && level->map->grid[level->coord.u][level->coord.v - 1] == '0')
    {
        level->coord.v -= 1;
        addRoomToFloor(level, level->coord.u, level->coord.v, level->bossRoom);
        updateMapLevel(level, level->coord.u, level->coord.v, level->map->boss);
        return 1;
    }
    return 0;
}

/**
 * @brief add one itemRoom next to a room
 *
 * @param level
 * @param itemRoom
 * @return int
 */
int addItemRoom(Level *level, Room *itemRoom)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (level->map->grid[i][j] == 'r')
            {
                if (putItemRoom(level, i, j, itemRoom))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// assistant to addItemRoom()
int putItemRoom(Level *level, int i, int j, Room *itemRoom)
{
    if (strcmp(itemRoom->type, "Item") && strcmp(itemRoom->type, "Bonus"))
    {
        return 0;
    }
    level->coord.u = i;
    level->coord.v = j;
    if (i > 0 && level->map->grid[i - 1][j] == '0')
    {
        level->coord.u -= 1;
        addRoomToFloor(level, i - 1, j, itemRoom);
        updateMapLevel(level, i - 1, j, level->map->item);
        return 1;
    }
    if (j < level->width - 1 && level->map->grid[i][j + 1] == '0')
    {
        level->coord.v += 1;
        addRoomToFloor(level, i, j + 1, itemRoom);
        updateMapLevel(level, i, j + 1, level->map->item);
        return 1;
    }
    if (i < level->height - 1 && level->map->grid[i + 1][j] == '0')
    {
        level->coord.u += 1;
        addRoomToFloor(level, i + 1, j, itemRoom);
        updateMapLevel(level, i + 1, j, level->map->item);
        return 1;
    }
    if (j > 0 && level->map->grid[i][j - 1] == '0')
    {
        level->coord.v -= 1;
        addRoomToFloor(level, i, j - 1, itemRoom);
        updateMapLevel(level, i, j - 1, level->map->item);
        return 1;
    }
    return 0;
}

void lockDoors(Level *level, int u, int v)
{
    if (level->floor[u][v].map[0][level->floor[u][v].columns / 2] != 'W')
    {
        northDoor(level, level->coord.u, level->coord.v, 'L');
    }
    if (level->floor[u][v].map[level->floor[u][v].rows / 2][0] != 'W')
    {
        westDoor(level, level->coord.u, level->coord.v, 'L');
    }
    if (level->floor[u][v].map[level->floor[u][v].rows - 1][level->floor[u][v].columns / 2] != 'W')
    {
        southDoor(level, level->coord.u, level->coord.v, 'L');
    }
    if (level->floor[u][v].map[level->floor[u][v].rows / 2][level->floor[u][v].columns - 1] != 'W')
    {
        eastDoor(level, level->coord.u, level->coord.v, 'L');
    }
}

void unlockDoors(Level *level, int u, int v)
{
    northDoor(level, u, v, level->currentRoom->upDoor);
    eastDoor(level, u, v, level->currentRoom->rightDoor);
    westDoor(level, u, v, level->currentRoom->leftDoor);
    southDoor(level, u, v, level->currentRoom->downDoor);
}

/**
 * @brief save doors of Rooms, Boss room and Bonus room
 *
 * @param level
 */
void saveCardinalDoors(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (!isType(level, i, j, "Wall"))
            {
                level->floor[i][j].upDoor = level->floor[i][j].map[0][level->columns / 2];
                level->floor[i][j].leftDoor = level->floor[i][j].map[level->rows / 2][0];
                level->floor[i][j].downDoor = level->floor[i][j].map[level->rows - 1][level->columns / 2];
                level->floor[i][j].rightDoor = level->floor[i][j].map[level->rows / 2][level->columns - 1];
            }
        }
    }
}

void hideBonusRoom(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (isType(level, i, j, "Room") || isType(level, i, j, "Spawner") || isType(level, i, j, "Item"))
            {
                hideCardinalDoors(level, i, j);
            }
        }
    }
}

void showBonusRoom(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (isType(level, i, j, "Room") || isType(level, i, j, "Spawner") || isType(level, i, j, "Item"))
            {
                showCardinalDoors(level, i, j);
            }
        }
    }
}

void putAllDoors(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (!isType(level, i, j, "Wall"))
            {
                putCardinalDoors(level, i, j);
            }
        }
    }
}

void putCardinalDoors(Level *level, int h, int w)
{
    putEastDoor(level, h, w);
    putSouthDoor(level, h, w);
    putWestDoor(level, h, w);
    putNorthDoor(level, h, w);
}
void hideCardinalDoors(Level *level, int h, int w)
{
    hideEastDoor(level, h, w);
    hideSouthDoor(level, h, w);
    hideWestDoor(level, h, w);
    hideNorthDoor(level, h, w);
}

void showCardinalDoors(Level *level, int h, int w)
{
    showEastDoor(level, h, w);
    showSouthDoor(level, h, w);
    showWestDoor(level, h, w);
    showNorthDoor(level, h, w);
}

void showEastDoor(Level *level, int u, int v)
{
    if (v < level->width - 1)
    {
        if (isType(level, u, v + 1, "Bonus"))
        {
            eastDoor(level, u, v, level->floor[u][v].rightDoor);
        }
    }
}

void showSouthDoor(Level *level, int u, int v)
{
    if (u < level->height - 1)
    {
        if (isType(level, u + 1, v, "Bonus"))
        {
            southDoor(level, u, v, level->floor[u][v].downDoor);
        }
    }
}

void showWestDoor(Level *level, int u, int v)
{
    if (v > 0)
    {
        if (isType(level, u, v - 1, "Bonus"))
        {
            westDoor(level, u, v, level->floor[u][v].leftDoor);
        }
    }
}

void showNorthDoor(Level *level, int u, int v)
{
    if (u > 0)
    {
        if (isType(level, u - 1, v, "Bonus"))
        {
            northDoor(level, u, v, level->floor[u][v].upDoor);
        }
    }
}

void hideEastDoor(Level *level, int u, int v)
{
    if (v < level->width - 1)
    {
        if (isType(level, u, v + 1, "Bonus"))
        {
            eastDoor(level, u, v, 'W');
        }
    }
}

void hideSouthDoor(Level *level, int u, int v)
{
    if (u < level->height - 1)
    {
        if (isType(level, u + 1, v, "Bonus"))
        {
            southDoor(level, u, v, 'W');
        }
    }
}

void hideWestDoor(Level *level, int u, int v)
{
    if (v > 0)
    {
        if (isType(level, u, v - 1, "Bonus"))
        {
            westDoor(level, u, v, 'W');
        }
    }
}

void hideNorthDoor(Level *level, int u, int v)
{
    if (u > 0)
    {
        if (isType(level, u - 1, v, "Bonus"))
        {
            northDoor(level, u, v, 'W');
        }
    }
}

void putEastDoor(Level *level, int h, int w)
{
    if (w < level->width - 1)
    {
        if (isType(level, h, w + 1, "Room"))
        {
            eastDoor(level, h, w, 'D');
        }
        if (isType(level, h, w + 1, "Item"))
        {
            eastDoor(level, h, w, '$');
        }
        if (isType(level, h, w + 1, "Bonus")) // room "Bonus" cachée
        {
            eastDoor(level, h, w, 'J');
        }
        if (isType(level, h, w + 1, "Boss"))
        {
            eastDoor(level, h, w, 'B');
        }
        if (isType(level, h, w + 1, "Spawner"))
        {
            eastDoor(level, h, w, 'D');
        }
        if (isType(level, h, w + 1, "Wall"))
        {
            eastDoor(level, h, w, 'W');
        }
    }
    else if (w == level->width - 1)
    {
        eastDoor(level, h, w, 'W');
    }
}

void putSouthDoor(Level *level, int h, int w)
{
    if (h < level->height - 1)
    {
        if (isType(level, h + 1, w, "Room"))
        {
            southDoor(level, h, w, 'D');
        }
        if (isType(level, h + 1, w, "Item"))
        {
            southDoor(level, h, w, '$');
        }
        if (isType(level, h + 1, w, "Bonus")) // room "Bonus" cachée
        {
            southDoor(level, h, w, 'J');
        }
        if (isType(level, h + 1, w, "Boss"))
        {
            southDoor(level, h, w, 'B');
        }
        if (isType(level, h + 1, w, "Spawner"))
        {
            southDoor(level, h, w, 'D');
        }
        if (isType(level, h + 1, w, "Wall"))
        {
            southDoor(level, h, w, 'W');
        }
    }
    else if (h == level->height - 1)
    {
        southDoor(level, h, w, 'W');
    }
}

void putWestDoor(Level *level, int h, int w)
{
    if (w > 0)
    {
        if (isType(level, h, w - 1, "Room"))
        {
            westDoor(level, h, w, 'D');
        }
        if (isType(level, h, w - 1, "Item"))
        {
            westDoor(level, h, w, '$');
        }
        if (isType(level, h, w - 1, "Bonus")) // room "Bonus" cachée
        {
            westDoor(level, h, w, 'J');
        }
        if (isType(level, h, w - 1, "Boss"))
        {
            westDoor(level, h, w, 'B');
        }
        if (isType(level, h, w - 1, "Spawner"))
        {
            westDoor(level, h, w, 'D');
        }
        if (isType(level, h, w - 1, "Wall"))
        {
            westDoor(level, h, w, 'W');
        }
    }
    else if (w == 0)
    {
        westDoor(level, h, w, 'W');
    }
}

void putNorthDoor(Level *level, int h, int w)
{
    if (h > 0)
    {
        if (isType(level, h - 1, w, "Item"))
        {
            northDoor(level, h, w, '$');
        }
        if (isType(level, h - 1, w, "Room"))
        {
            northDoor(level, h, w, 'D');
        }
        if (isType(level, h - 1, w, "Bonus")) // room "Bonus" cachée
        {
            northDoor(level, h, w, 'J');
        }
        if (isType(level, h - 1, w, "Boss"))
        {
            northDoor(level, h, w, 'B');
        }
        if (isType(level, h - 1, w, "Spawner"))
        {
            northDoor(level, h, w, 'D');
        }
        if (isType(level, h - 1, w, "Wall"))
        {
            northDoor(level, h, w, 'W');
        }
    }
    else if (h == 0)
    {
        northDoor(level, h, w, 'W');
    }
}

void northDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[0][level->floor[u][v].columns / 2] = door; // map de la room
}

void eastDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[level->floor[u][v].rows / 2][level->floor[u][v].columns - 1] = door;
}

void southDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[level->floor[u][v].rows - 1][level->floor[u][v].columns / 2] = door;
}

void westDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[level->floor[u][v].rows / 2][0] = door;
}

int isKind(Level *level, int u, int v, char kind)
{
    return level->map->grid[u][v] == kind;
}
/**
 * @brief booléen sur le type de la room
 *
 * @param level
 * @param h vertical coordinate
 * @param w horizontal coordinate
 * @param type (Wall, Item, Spawner, Boss, Room ou Bonus)
 * @return int 1 if true, 0 otherwise
 */
int isType(Level *level, int u, int v, char *type)
{
    return !strcmp(level->floor[u][v].type, type);
}

void addRoomToFloor(Level *level, int i, int j, Room *r)
{
    // location of the room (u, v)
    r->spot.u = i;
    r->spot.v = j;

    // add Room r to the grid floor
    level->floor[i][j] = *r;
    level->floor[i][j].map = copyMapRoom(*r);
}

MonsterList *createMonsters(char *monsterfile)
{
    MonsterList *monsters = newMonsterList();
    MonsterList *monsterList = readMonsterFile(monsterfile);
    int numberOne = rand() % 7;
    int numberTwo = 0;
    if (numberOne < 6)
    {
        numberTwo = rand() % (7 - numberOne);
    }
    int index = rand() % monsterList->size;
    for (int i = 0; i < numberOne; i += 1)
    {
        addMonsterList(monsterList->list[index], monsters);
    }
    index = rand() % monsterList->size;
    for (int i = 0; i < numberTwo; i += 1)
    {
        addMonsterList(monsterList->list[index], monsters);
    }

    // Un monstre a 10% de chance d'être champion
    int random = rand() % 10;
    switch (random)
    {
    case 9:
        for (int i = 0; i < monsters->size; i += 1)
        {
            monsters->list[i]->champion = true;
            monsters->list[i]->hpMax *= 2;
            monsters->list[i]->dmg *= 2;
        }
        break;
        // default:
        // do nothing (not a champion)
    }
    return monsters;
}

void randomPointMonsters(Room room)
{
    // random positions of monsters in the room
    for (int i = 0; i < room.monsters->size; i += 1)
    {
        Monster *m = room.monsters->list[i];
        m->p.h = 0;
        m->p.w = 0;
        while (room.map[m->p.h][m->p.w] != ' ')
        {
            m->p.h = rand() % room.rows;
            m->p.w = rand() % room.columns;
        }
    }
}

/**
 * @brief Ajoute un nombre aléatoire de monstres dans la pièce et les place aléatoirement
 *
 * @param level
 * @param u
 * @param v
 * @param monsterfile
 */
void addMonstersToRoom(Level *level, int u, int v, char *monsterfile)
{
    level->floor[u][v].monsters = createMonsters(monsterfile);
    randomPointMonsters(level->floor[u][v]);
}

char **copyMapRoom(Room room)
{
    char **map;
    map = malloc(sizeof(char *) * room.rows);
    for (int i = 0; i < room.rows; i += 1)
    {
        map[i] = malloc(sizeof(char) * room.columns);
    }
    for (int i = 0; i < room.rows; i += 1)
    {
        for (int j = 0; j < room.columns; j += 1)
        {
            map[i][j] = room.map[i][j];
        }
    }
    return map;
}

void freeLevel(Level *level)
{
    free(level->pathRoomfile);
    free(level->pathItemfile);
    free(level->pathMonsterfile);
    freeRoom(level->bossRoom);
    freeRoom(level->itemRoomBonus);
    freeRoom(level->itemRoom);
    freeRoom(level->spawner);
    freeRoom(level->currentRoom);
    freeMap(level->map);
    for (int i = 0; i < level->height; i += 1)
    {
        free(level->floor[i]);
    }
    free(level->floor);
    free(level);
}

void showFloor(Level *level)
{
    char *str;
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            printf("\n%d-%d ++++++++++++++++\n", i, j);
            showRoom(level->floor[i][j]);
        }

        printf("------------\n");
    }
}

/**
 * @brief update la carte de l'étage à l'emplacement (i, j)
 *
 * @param map
 * @param i
 * @param j
 * @param kind (r, S, I, J, B, 0) = (Room, Spawner, Item, Bonus, Boss, Wall)
 */
void updateMapLevel(Level *level, int i, int j, char kind)
{
    level->map->grid[i][j] = kind;
}
