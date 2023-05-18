//
// Created by Eric Bjarstal on 14/05/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"


int strcmpSansCasse(char* str1, char* str2) {
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

T_Position *creerPosition(int ligne, int ordre, int phrase) {

    // création de l'instance de la position à ajouter
    T_Position *nouvellePosition = malloc(sizeof(T_Position));
    if (!nouvellePosition) {
        printf("\nErreur creation nouvelle instance T_Position");
        return NULL;
    }

    // initialisation des attributs
    nouvellePosition->numeroLigne = ligne;
    nouvellePosition->ordre = ordre;
    nouvellePosition->numeroPhrase = phrase;
    nouvellePosition->suivant = NULL;

    return nouvellePosition;
}

T_Noeud *creerNoeud(char* mot) {

    T_Noeud *nouveauNoeud = malloc(sizeof(T_Noeud));
    if (!nouveauNoeud) {
        printf("\nErreur creation nouvelle instance T_Noeud");
        return NULL;
    }

    // initialisation des attributs
    nouveauNoeud->mot = strdup(mot);
    nouveauNoeud->nbOccurrences = 1;
    nouveauNoeud->listePositions = NULL;
    nouveauNoeud->filsDroit = NULL;
    nouveauNoeud->filsGauche = NULL;

    return nouveauNoeud;
}

T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase) {

    T_Position *premierElement = listeP;

    // création de l'instance de la position à ajouter
    T_Position *position_a_ajouter = creerPosition(ligne, ordre, phrase);

    // si listeP est vide
    if (!listeP) {
        premierElement = position_a_ajouter;
        return premierElement;
    }

    // s'il faut placer le nouvel élément au début de listeP
    if (position_a_ajouter->numeroLigne <= listeP->numeroLigne && position_a_ajouter->ordre <= listeP->ordre) {
        position_a_ajouter->suivant = premierElement;
        premierElement = position_a_ajouter;
        return premierElement;
    }

    while (listeP) {

        // s'il faut placer le nouvel élément à la fin de listeP
        if (!(listeP->suivant)) {
            listeP->suivant = position_a_ajouter;
            return premierElement;
        }

        // ici, on sait que listeP suivant existe
        if (position_a_ajouter->numeroLigne <= listeP->suivant->numeroLigne) {
            if (position_a_ajouter->ordre <= listeP->suivant->ordre) {
                position_a_ajouter->suivant = listeP->suivant;
                listeP->suivant = position_a_ajouter;
                return premierElement;
            }
        }

        listeP = listeP->suivant;
    }

    return premierElement;
}

int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase) {
    int comparaison = 0;

    if (!index || !mot) {
        printf("\nErreur ajouterOccurence(): index ou mot n'existe pas.");
        return 0;
    }

    T_Noeud *noeud = creerNoeud(mot);
    noeud->listePositions = creerPosition(ligne, ordre, phrase);

    if (!index->racine) {
        index->racine = noeud;
        index->nbMotsDistincts = 1;
        index->nbMotsTotal = 1;
        return 1;
    }
    T_Noeud *noeudCourant = index->racine;
    while (noeudCourant) {
        comparaison = strcmpSansCasse(mot, noeudCourant->mot);
        if (comparaison == 0) {
            // Vérifier si la position existe déjà dans la liste des positions du mot
            T_Position* positionCourante = noeudCourant->listePositions;
            while (positionCourante) {
                if (positionCourante->numeroLigne == ligne &&
                    positionCourante->ordre == ordre &&
                    positionCourante->numeroPhrase == phrase) {
                    // La position existe déjà, aucune action nécessaire
                    return 1;
                }
                positionCourante = positionCourante->suivant;
            }

            // La position n'existe pas, ajouter la nouvelle position
            noeudCourant->nbOccurrences++;
            noeudCourant->listePositions = ajouterPosition(noeudCourant->listePositions, ligne, ordre, phrase);
            index->nbMotsTotal++;
            return 1;
        }
        else if (comparaison < 0) {
            if (noeudCourant->filsGauche) {
                noeudCourant = noeudCourant->filsGauche;
            }
            else {
                noeudCourant->filsGauche = noeud;
                index->nbMotsDistincts++;
                index->nbMotsTotal++;
                return 1;
            }
        }
        else {
            if (noeudCourant->filsDroit) {
                noeudCourant = noeudCourant->filsDroit;
            }
            else {
                noeudCourant->filsDroit = noeud;
                index->nbMotsDistincts++;
                index->nbMotsTotal++;
                return 1;
            }
        }
    }
    printf("\nErreur ajouterOccurence(): l'occurrence n'a pas pu être ajoutée.");
    return 0;
}
