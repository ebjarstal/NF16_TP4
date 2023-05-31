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
    if (!nouveauNoeud->mot) {
        free(nouveauNoeud); // libère la mémoire allouée pour le nouveau nœud
        printf("\nErreur creation nouvelle instance T_Noeud");
        return NULL;
    }
    nouveauNoeud->nbOccurrences = 1;
    nouveauNoeud->listePositions = NULL;
    nouveauNoeud->filsDroit = NULL;
    nouveauNoeud->filsGauche = NULL;

    return nouveauNoeud;
}

T_Index creerIndexTemporaire(T_Noeud* racine, int nbMotsDistincts, int nbMotsTotal) {
    T_Index nouveauIndex;
    nouveauIndex.racine = racine;
    nouveauIndex.nbMotsDistincts = nbMotsDistincts;
    nouveauIndex.nbMotsTotal = nbMotsTotal;

    return nouveauIndex;
}

T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase) {
    T_Position *premierElement = listeP;
    T_Position *position_a_ajouter = creerPosition(ligne, ordre, phrase);

    if (!position_a_ajouter) {
        return premierElement; // Retourner la liste d'origine sans modification
    }

    // Si listeP est vide ou si la position doit être placée en tête de liste
    if (!listeP || (ligne < listeP->numeroLigne) || (ligne == listeP->numeroLigne && ordre <= listeP->ordre)) {
        position_a_ajouter->suivant = listeP;
        return position_a_ajouter;
    }

    T_Position *precedent = NULL;
    T_Position *courant = listeP;

    while (courant) {
        if ((ligne < courant->numeroLigne) || (ligne == courant->numeroLigne && ordre <= courant->ordre)) {
            position_a_ajouter->suivant = courant;
            if (precedent) {
                precedent->suivant = position_a_ajouter;
                return premierElement;
            } else {
                return position_a_ajouter;
            }
        }

        precedent = courant;
        courant = courant->suivant;
    }

    precedent->suivant = position_a_ajouter;
    return premierElement;
}


int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase) {
    int comparaison = 0;

    if (!index || !mot) {
        printf("\nErreur ajouterOccurence(): index ou mot existe pas.");
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
    printf("\nErreur ajouterOccurence(): occurrence a pas pu être ajoutee");
    return 0;
}

// renvoie -1 si erreur
// la fonction marche mal si le dernier caractère n'est pas un point, un espace ou un \n
// A régler
int indexerFichier(T_Index *index, char *filename) {
    int nbMots = 0, numLigne = 1, ordre = 1, numPhrase = 1, tailleMot = 0;
    char mot[TAILLE_MAX_MOT];
    char c, suivant;

    FILE *fichier;
    fichier = fopen(filename, "r");

    if (fichier == NULL) {
        printf("\nErreur indexerFichier(): %s n'a pas pu être ouvert", filename);
        return -1;
    }

    c = fgetc(fichier);
    while (c != EOF) {
        char tmp = fgetc(fichier);
        if (tmp == EOF) {
            mot[tailleMot] = c;
            mot[tailleMot+1] = '\0';
            ajouterOccurence(index, mot, numLigne, ordre, numPhrase);
            // printf("\najout de %s a index", mot);
            return nbMots+1;
        }
        ungetc(tmp, fichier);

        if (c == '\n' || c == ' ' || c == '.') {  // si on a terminé un mot
            mot[tailleMot] = '\0';
            if (mot[0] != '\0') {
                // printf("\najout de %s a index", mot);
                ajouterOccurence(index, mot, numLigne, ordre, numPhrase);
                nbMots++;
            }
            ordre++;
            tailleMot = 0;
            if (tmp == EOF) {return nbMots;}
        } else if (isalpha(c)) {  // si c'est une lettre
            mot[tailleMot] = c;
            tailleMot++;
        } else if (c == '\"' || c == '\'') {  // si c'est un guillemet
            mot[tailleMot] = c;
            tailleMot++;
            suivant = fgetc(fichier);
            while (suivant != c) {
                mot[tailleMot] = suivant;
                tailleMot++;
                suivant = fgetc(fichier);
            }
            mot[tailleMot] = suivant;
            tailleMot++;
        } else if (c == '?') {  // si c'est un point d'interrogation
            numPhrase++;
        }

        if (c == '\n') {  // si on a terminé une ligne
            numLigne++;
            ordre = 1;
        }

        c = fgetc(fichier);
    }

    fclose(fichier);

    return nbMots;
}


void afficherIndex(T_Index index) {
    if (index.racine == NULL) {
        printf("\nErreur afficherIndex(): index vide");
        return;
    }
//    T_Noeud *noeud = index.racine;
//    while (noeud) {
//        printf("\n%s", noeud->mot);
//        noeud = noeud->filsGauche;
//    }
    afficherMots(index.racine, &index.racine->mot[0]);
}

//void afficherMots(T_Noeud *noeud, char premiereLettrePrecedente) { test
//    if (noeud != NULL) {
//        // affiche les mots du sous-arbre gauche (mots inférieurs)
//        if (noeud->filsGauche != NULL) {
//            afficherMots(noeud->filsGauche, premiereLettrePrecedente);
//        }
//
//        if (tolower(noeud->mot[0]) != tolower(premiereLettrePrecedente)) {
//            printf("\n\n%c", toupper(noeud->mot[0]));  // convertit la lettre en majuscule pour l'affichage
//            premiereLettrePrecedente = noeud->mot[0];
//        }
//
//        // affiche le mot courant et ses informations
//        printf("\n|-- %s", noeud->mot);
//        afficherPositions(noeud->listePositions);
//
//        // affiche les mots du sous-arbre droit (mots supérieurs)
//        if (noeud->filsDroit != NULL) {
//            afficherMots(noeud->filsDroit, premiereLettrePrecedente);
//        }
//    }
//}


void afficherPositions(T_Position *listeP) {
    T_Position *position = listeP;

    while (position != NULL) {
        printf("\n|--- (l:%d, o:%d, p:%d) ", position->numeroLigne, position->ordre, position->numeroPhrase);
        position = position->suivant;
    }
    printf("\n|");
}

T_Noeud *rechercherMot(T_Index index, char *mot) {
    if (!mot) {
        printf("\nErreur rechercherMot(): mot pas defini");
        return NULL;
    }

    T_Noeud *racine = index.racine;
    while (racine) {
        int comparaison = strcmpSansCasse(racine->mot, mot);
        if (comparaison == 0) {
            return racine;
        } else if (comparaison > 0) {
            racine = racine->filsGauche;/**/
        } else {
            racine = racine->filsDroit;
        }
    }

    return NULL;  // si le mot n'a pas été trouvé
}
