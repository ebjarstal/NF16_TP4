//
// Created by Eric Bjarstal on 14/05/2023.
// salut

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tp4.h"


int main() {
    char *premierMot = "bonjour";
    char *secondMot = "Bonjour";
    char *troisiemeMot = "Test";
    printf("\n%d", strcmp(premierMot, secondMot));  // test
    return 0;
}
