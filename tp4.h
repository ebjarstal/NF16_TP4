//
// Created by Eric Bjarstal on 14/05/2023.
//

#ifndef NF16_TP4_TP4_H
#define NF16_TP4_TP4_H

// STRUCTURES DE DONNEES

typedef struct Position T_Position;
struct Position {
    int numeroLigne;
    int ordre;
    int numeroPhrase;
    struct Position* suivant;
};

typedef struct Noeud T_Noeud;
struct Noeud {
    char* mot;
    int nbOccurrences;
    T_Position* listePositions;
    struct Noeud* filsGauche;
    struct Noeud* filsDroit;
};

typedef struct Index T_Index;
struct Index {
    T_Noeud* racine;
    int nbMotsDistincts;
    int nbMotsTotal;
};

// FONCTIONS DE BASE
int strcmpSansCasse(char* str1, char* str2);

T_Position *creerPosition(int ligne, int ordre, int phrase);

// permet d’ajouter un élément dans une liste de positions triées
T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase);

int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase);

#endif //NF16_TP4_TP4_H
