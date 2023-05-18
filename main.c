//
// Created by Eric Bjarstal on 14/05/2023.
// salut

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"


int main() {
    char *premierMot = "bonjour";
    char *secondMot = "Bonjour";
    printf("\n%d", strcmpSansCasse(premierMot, secondMot));
    return 0;
}
