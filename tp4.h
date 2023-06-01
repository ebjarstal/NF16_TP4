//
// Created by Eric Bjarstal on 14/05/2023.
//

#ifndef NF16_TP4_TP4_H
#define NF16_TP4_TP4_H
#define TAILLE_MAX_MOT 100
#define TAILLE_MAX_PHRASE 1000


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

typedef struct Mot T_Mot;
struct Mot {
    char *mot;
    T_Position *position;
    T_Mot *suivant;
};

typedef struct Phrase T_Phrase;
struct Phrase {
    T_Mot *listeMots;
    T_Phrase *suivante;
};

typedef struct Index T_Index;
struct Index {
    T_Noeud* racine;
    int nbMotsDistincts;
    int nbMotsTotal;
    T_Phrase *listePhrases;
};

// FONCTIONS DE BASE
int strcmpSansCasse(char* str1, char* str2);

T_Position *creerPosition(int ligne, int ordre, int phrase);
T_Noeud *creerNoeud(char* mot);

T_Mot *creerMot(char *mot, T_Position *position);
T_Phrase *creerPhrase();
T_Phrase *ajouterMot(T_Mot *mot, T_Phrase *phrase);

// permet d’ajouter un élément dans une liste de positions triées
T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase);

int ajouterOccurence(T_Index *index, char *mot, int ligne, int ordre, int phrase);

int indexerFichier(T_Index *index, char *filename);

void afficherIndex(T_Index *index);
void afficherMots(T_Noeud *noeud, char *derniereLettre);
void afficherPositions(T_Position *listeP);
void afficherOccurrencesMot(T_Index *index, char *mot);
void construireTexte(T_Index index, char *filename);

T_Noeud *rechercherMot(T_Index *index, char *mot);
void clear_input_buffer();




#endif //NF16_TP4_TP4_H