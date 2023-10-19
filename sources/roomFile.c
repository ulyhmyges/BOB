/*
**  Filename : roomFile.c
**
**  Made by : HT
**
**  Description : editor of a file full of rooms *.rtbob
*/

#include "roomFile.h"

/**
 * @brief écrit dans fichier les éléments du tableau roomList.list
 * 
 * @param roomList objet contenant la liste des pièces
 * @param fichier chemin du fichier *.rtbob à créer
 */
void writeRoomFile(RoomList roomList, char *fichier)
{
    FILE *file = fopen(fichier, "w");
    // vérifie si le pointeur file est bien alloué
    if (file != NULL)
    {
        printRoomList(roomList, file);
        fclose(file);
    }
    else
    {
        printf("Erreur lors de l'écriture du fichier!");
    }
}

/**
 * @brief Ajoute une pièce à la fin du fichier
 * 
 * @param room la pièce à ajouter
 * @param fichier chemin du fichier *.rtbob à modifier
 */
void addRoomFile(Room room, char *fichier){
    FILE *file = fopen(fichier, "r+");
    if (file != NULL){
        fseek(file, 0, SEEK_END);   // déplacement du curseur à la fin du fichier
        printRoom(room, file);
        fseek(file, 0, SEEK_SET);   // déplacement du curseur au début du fichier
        int nbrooms = -1;
        if (fscanf(file, "{%d}", &nbrooms) == -1){
            printf("Erreur fscanf dans addRoomFile!\n");
        }
        fseek(file, 0, SEEK_SET);   // déplacement du curseur à la position 1
        fprintf(file, "{%d}\n", nbrooms + 1);   // ajoute 1 au nombre total de pièces
        fclose(file);
    } else {
        printf("Erreur de lecture/écriture avec le fichier: %s\n", fichier);
    }
}

/**
 * @brief supprime la pièce dans le fichier selon l'id
 * 
 * @param id attribut d'une pièce
 * @param fichier chemin du fichier *.rtbob à modifier
 */
void removeRoomFileById(int id, char *fichier, char *monsterfile){
    RoomList *roomList = readRoomFile(fichier, monsterfile);
    for (int i = 0; i < roomList->size; i += 1) {
        if (roomList->list[i]->id == id){
            removeByRoom(roomList, roomList->list[i]);
        }
    }
    writeRoomFile(*roomList, fichier);
}

/**
 * @brief supprime une pièce selon sa position dans le fichier
 * 
 * @param index commence à partir de 0
 * @param fichier chemin du fichier *.rtbob à modifier
 */
void removeRoomFileByIndex(int index, char *fichier, char *monsterfile){
    RoomList *roomList = readRoomFile(fichier, monsterfile);
    removeByIndex(roomList, index);
    writeRoomFile(*roomList, fichier);
}

/**
 * @brief affiche une pièce du fichier choisie par id
 * 
 * @param id attribut de la pièce
 * @param fichier chemin du fichier *.rtbob
 */
void showRoomFileById(int id, char *fichier, char *monsterfile){
    RoomList *roomList = NULL;
    roomList = readRoomFile(fichier, monsterfile);
    int j = 0;
    for (int i = 0; i < roomList->size; i += 1){    // à la 1ère occurrence de l'id dans la liste, on sort de la boucle
        if (roomList->list[i]->id == id){
            showRoom(*roomList->list[i]);
            break;
        }
    }
    freeRoomList(roomList);
    roomList = NULL;
    printf("showRomFileById - freeRoomList: %p\n", roomList);
}

/**
 * @brief ouvre le fichier, récupère l'ensemble des pièces sous forme d'un pointeur RoomList et ferme le fichier
 * 
 * @param fichier chemin du fichier *.rtbob à lire
 * @return RoomList* l'ensemble des pièces contenues dans le fichier 'fichier'
 */
RoomList * readRoomFile(char *roomfile, char *monsterfile){
    RoomList *roomList = newRoomList();

    FILE *f = fopen(roomfile, "r");
    if (f != NULL)
    {
        fscanf(f, "{%d}\n", &roomList->size);
        for (int i = 0; i < roomList->size; i += 1){
            roomList->list[i] = readRoom(f, monsterfile);
        }
        fclose(f);
        return roomList;
    }else{
        return NULL;
    }
}

/**
 * @brief retourne un pointeur de la pièce 
 * après avoir lu les attributs :
 * => rows, columns et id dans un premier temps puis l'attribut
 * => map dans un second temps
 * 
 * @param f file in read state 
 * @return Room* la pièce
 */
Room* readRoom(FILE *f, char *monsterfile)
{
    // fonction auxiliaire à readRoomFile()
    int rows = 0;
    int columns = 0;
    int id = 0;
    fscanf(f, "[%d|%d]%d\n", &rows, &columns, &id);
    Room* room = newRoom(rows, columns, "Room", 0, monsterfile); // room vide sans porte
    room->id = id;
    for (int i = 0; i < room->rows; i += 1)
    {
        for (int j = 0; j < room->columns + 1; j += 1)
        {
            if (j == room->columns)
            {
                fgetc(f);
                continue;
            }
            room->map[i][j] = fgetc(f);
        }
    }
    
    return room;
}