//
// Created by Eric Bjarstal on 14/05/2023.
// salut

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"

void test() {
    T_Index index;
    index.racine = NULL;
    index.nbMotsDistincts = 0;
    index.nbMotsTotal = 0;
    char *motCherche = "tonton";

    char filename[] = "/Users/ericb/Desktop/NF16_TP4/texte.txt";
    int result = indexerFichier(&index, filename);

    if (result == -1) {
        printf("\nErreur lors de l'ouverture du fichier %s.", filename);
        return;
    }

    printf("\nNombre total de mots : %d", result);
    printf("\nNombre de mots distincts : %d", index.nbMotsDistincts);
    printf("\nIndexation terminée.");
    T_Noeud *resultatRechercheMot = rechercherMot(index, motCherche);
    if (resultatRechercheMot) {
        printf("\n%s trouve. %d occurrences", motCherche, resultatRechercheMot->nbOccurrences);
    }
    else {printf("\n%s pas trouve.", motCherche);}
    afficherIndex(index);
}


int main() {
    test();
    printf("\n%d", strcmpSansCasse("sappelle", "Simon"));
    return 0;
}
