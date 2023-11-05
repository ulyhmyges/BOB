/*
**  Filename : monster.h
**
**  Made by : HT
**
**  Description : model of a monster
*/

#ifndef MONSTER_H

#define MONSTER_H
#include "item.h"
#include "map.h"

typedef struct Monster {
    char *name;
    float hpMax;        //barre de vie maximum
    float dmg;
    boolean shoot;      //true: tir ou false: monstre se dirige vers vous
    boolean ss;         //tir traverse les rochers
    boolean flight;     //vol au dessus : rocher, trou, pic
    Point p;
} Monster;

Monster * newMonster(char *name, float hpMax, float dmg, boolean shoot, boolean ss, boolean flight);
void freeMonster(Monster *monster);
void showMonster(Monster monster);
void printMonster(Monster monster, FILE *f);
Monster * readMonster(FILE *f);

Monster* askMonster(Monster* monster);

#endif // MONSTER_H