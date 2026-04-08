#include <stdlib.h>
#include "analyseur.h"

Noeud* creer_noeud(Jeton type) {
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    if (n) {
        n->type = type;
        n->valeur[0] = '\0';
        n->premier_fils = NULL;
        n->frere_suivant = NULL;
    }
    return n;
}