#ifndef ARBRE_H
#define ARBRE_H

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
} Jeton;

typedef struct Noeud {
    Jeton type;
    char valeur[512];              // Pour stocker le texte des MOTS ou TITRES
    struct Noeud* premier_fils;    // Pointeur vers le premier enfant (en dessous)
    struct Noeud* frere_suivant;   // Pointeur vers l'élément suivant (à côté)
} Noeud;

#endif