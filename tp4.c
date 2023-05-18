//
// Created by Eric Bjarstal on 14/05/2023.
//dazfnianzfoianzifniao

#include <stdlib.h>
#include <stdio.h>
#include "tp4.h"

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