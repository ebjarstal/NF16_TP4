//
// Created by Eric Bjarstal on 14/05/2023.
// salut

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"

//void test() {
//    T_Index index;
//    index.racine = NULL;
//    index.nbMotsDistincts = 0;
//    index.nbMotsTotal = 0;
//    char *motCherche = "tonton";
//
//    char filename[] = "/Users/ericb/Desktop/NF16_TP4/texte.txt";
//    int result = indexerFichier(&index, filename);
//
//    if (result == -1) {
//        printf("\nErreur lors de l'ouverture du fichier %s.", filename);
//        return;
//    }
//
//    printf("\nNombre total de mots : %d", result);
//    printf("\nNombre de mots distincts : %d", index.nbMotsDistincts);
//    printf("\nIndexation terminée.");
//    T_Noeud *resultatRechercheMot = rechercherMot(index, motCherche);
//    if (resultatRechercheMot) {
//        printf("\n%s trouve. %d occurrences", motCherche, resultatRechercheMot->nbOccurrences);
//    }
//    else {printf("\n%s pas trouve.", motCherche);}
//    afficherIndex(index);

void afficherMenu() {
        printf("\nMenu :");
        printf("\n1. Charger un fichier");
        printf("\n2. Caracteristiques de l'index");
        printf("\n3. Afficher l'index");
        printf("\n4. Rechercher un mot");
        printf("\n5. Afficher les occurrences d'un mot");
        printf("\n6. Construire le texte a partir de l'index");
        printf("\n7. Quitter");
}

int main() {
    T_Index *index = malloc(sizeof(T_Index));
    index->racine = NULL;
    index->nbMotsDistincts = 0;
    index->nbMotsTotal = 0;
    index->listePhrases = creerPhrase();

    int choix = 0;
    char filename[TAILLE_MAX_MOT];
    char motRecherche[TAILLE_MAX_MOT];

    while (choix != 7) {
        afficherMenu();
        printf("\n\nEntrez votre choix (1-7) : ");
        scanf("%d", &choix);
        clear_input_buffer();

        switch (choix) {
            case 1:
                printf("\nEntrez le nom du fichier : ");
                scanf("%s", filename);
                clear_input_buffer();

                if (indexerFichier(index, filename) != -1) {
                    printf("\nLe fichier a ete charge avec succes.");
                } else {
                    printf("\nErreur lors du chargement du fichier.");
                }
                break;


            case 2:
                printf("\nCaracteristiques de l'index :");
                printf("\nNombre de mots distincts : %d", index->nbMotsDistincts);
                printf("\nNombre total de mots : %d", index->nbMotsTotal);
                break;

            case 3:
                printf("\nAffichage de l'index :");
                afficherIndex(index);
                break;

            case 4:
                printf("\nEntrez le mot a rechercher : ");
                scanf("%s", motRecherche);
                clear_input_buffer();

                T_Noeud* resultat = rechercherMot(index, motRecherche);
                if (resultat != NULL) {
                    printf("\nOccurrences du mot '%s' :", motRecherche);
                    afficherPositions(resultat->listePositions);
                } else {
                    printf("\nLe mot '%s' n'a pas ete trouve dans l'index.", motRecherche);
                }
                break;

            case 5:
                printf("\nEntrez le mot a rechercher : ");
                scanf("%s", motRecherche);
                clear_input_buffer();
                afficherOccurrencesMot(index, motRecherche);
                break;

            case 6:
                printf("\nEntrez le nom du nouveau fichier : ");
                char nomNouveauFichier[TAILLE_MAX_MOT];
                scanf("%s", nomNouveauFichier);
                clear_input_buffer();
                construireTexte(*index, nomNouveauFichier);
                break;

            case 7:
                free(index);
                exit(0);

            default:
                printf("\nChoix invalide. Veuillez reessayer.");
                break;
        }

        printf("\n");
    }

    return 0;
}
