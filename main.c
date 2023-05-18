//
// Created by Eric Bjarstal on 14/05/2023.
// salut

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"


void testAjouterOccurence() {
    T_Index *index = malloc(sizeof(T_Index));
    index->racine = NULL;
    index->nbMotsDistincts = 0;
    index->nbMotsTotal = 0;

    // Ajout de mots dans l'index
    ajouterOccurence(index, "hello", 1, 1, 1);
    ajouterOccurence(index, "world", 1, 2, 1);
    ajouterOccurence(index, "hello", 2, 1, 2);
    ajouterOccurence(index, "world", 2, 2, 2);
    ajouterOccurence(index, "world", 3, 1, 3);

    // Affichage du nombre de mots distincts et total dans l'index
    printf("\nNombre de mots distincts : %d\n", index->nbMotsDistincts);
    printf("\nNombre de mots total : %d\n", index->nbMotsTotal);
}

int main() {
    testAjouterOccurence();
    return 0;
}
