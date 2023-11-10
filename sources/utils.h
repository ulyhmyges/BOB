/*
**  Filename : utils.h
**
**  Made by : people
**
**  Description : useful functions from web
*/

#ifndef UTILS_H
#define UTILS_H

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//#include <unistd.h>
#include <stdio.h>

void clearScreen(void);
int kbhit(void);

#endif // UTILS_H