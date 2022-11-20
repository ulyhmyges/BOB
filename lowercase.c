#include <stdio.h>
#include <string.h>
#include "lowercase.h"

void lowercase(char* str) {
    for (int i = 0; i < strlen(str); i += 1 ) {
        if (str[i] > 64 && str[i] < 91) {
            str[i] = str[i] + 32;
        }
    }
}