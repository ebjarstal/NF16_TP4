//
// Created by Eric Bjarstal on 14/05/2023.
// salut

#include <stdlib.h>
#include <stdio.h>
#include "tp4.h"


void afficherListe(T_Position* listeP) {
    T_Position* position = listeP;
    while (position) {
        printf("(%d, %d, %d) -> ", position->numeroLigne, position->ordre, position->numeroPhrase);
        position = position->suivant;
    }
    printf("NULL\n");
}


void testAjouterPosition() {
    T_Position* listeP = NULL;

    // Test case 1
    listeP = ajouterPosition(listeP, 1, 2, 3);
    printf("ListeP after adding position (1, 2, 3):\n");
    afficherListe(listeP);

    // Test case 2
    listeP = ajouterPosition(listeP, 2, 1, 4);
    printf("\nListeP after adding position (2, 1, 4):\n");
    afficherListe(listeP);

    // Test case 3
    listeP = ajouterPosition(listeP, 0, 0, 5);
    printf("\nListeP after adding position (0, 0, 5):\n");
    afficherListe(listeP);
}


int main() {
    testAjouterPosition();
    return 0;
}
