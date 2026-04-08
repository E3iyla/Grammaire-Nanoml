#ifndef ARBRE_H
#define ARBRE_H

// L'énumération de toutes nos balises
typedef enum {
    DOC_OPEN, DOC_CLOSE,
    SEC_OPEN, SEC_CLOSE,
    ANN_OPEN, ANN_CLOSE,
    TITRE_OPEN, TITRE_CLOSE,
    LISTE_OPEN, LISTE_CLOSE,
    ITEM_OPEN, ITEM_CLOSE,
    BR,
    MOT,
    FIN_FICHIER
} t_jeton;

// La structure de notre arbre
typedef struct Noeud {
    t_jeton type;
    char valeur[512];
    struct Noeud* premier_fils;
    struct Noeud* frere_suivant;
} Noeud;

// Le prototype pour créer un noeud
Noeud* creer_noeud(t_jeton type);

#endif