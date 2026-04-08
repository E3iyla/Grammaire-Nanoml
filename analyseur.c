#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyseur.h"

// Prototypes pour la récursion
Noeud* parse_items();
Noeud* parse_annexes();

// Point d'entrée principal
Noeud* parse_texte_enrichi() {
    Noeud* racine = parse_document();
    if (jeton_courant == ANN_OPEN) {
        racine->frere_suivant = parse_annexes();
    }
    return racine;
}

Noeud* parse_annexes() {
    if (jeton_courant == ANN_OPEN) {
        verifier(ANN_OPEN);
        Noeud* n = creer_noeud(ANN_OPEN);
        n->premier_fils = parse_contenu();
        verifier(ANN_CLOSE);
        n->frere_suivant = parse_annexes();
        return n;
    }
    return NULL;
}

Noeud* parse_contenu() {
    // On vérifie si le jeton actuel peut démarrer du contenu
    if (jeton_courant == MOT || jeton_courant == SEC_OPEN || 
        jeton_courant == TITRE_OPEN || jeton_courant == BR || jeton_courant == LISTE_OPEN) {
        
        Noeud* n = NULL;
        
        if (jeton_courant == MOT) {
            n = creer_noeud(MOT);
            // Copie de la valeur textuelle depuis analyseur.h
            strcpy(n->valeur, valeur_courante); 
            suivant();
        } 
        else if (jeton_courant == BR) {
            n = creer_noeud(BR);
            suivant();
        } 
        else if (jeton_courant == SEC_OPEN) {
            verifier(SEC_OPEN);
            n = creer_noeud(SEC_OPEN);
            n->premier_fils = parse_contenu();
            verifier(SEC_CLOSE);
        } 
        else if (jeton_courant == TITRE_OPEN) {
            verifier(TITRE_OPEN);
            n = creer_noeud(TITRE_OPEN);
            n->premier_fils = parse_contenu();
            verifier(TITRE_CLOSE);
        } 
        else if (jeton_courant == LISTE_OPEN) {
            verifier(LISTE_OPEN);
            n = creer_noeud(LISTE_OPEN);
            n->premier_fils = parse_items();
            verifier(LISTE_CLOSE);
        }
        
        // Récursion pour lire la suite du contenu au même niveau
        if (n) n->frere_suivant = parse_contenu();
        return n;
    }
    return NULL;
}

Noeud* parse_items() {
    if (jeton_courant == ITEM_OPEN) {
        verifier(ITEM_OPEN);
        Noeud* n = creer_noeud(ITEM_OPEN);
        n->premier_fils = parse_contenu();
        verifier(ITEM_CLOSE);
        n->frere_suivant = parse_items();
        return n;
    }
    return NULL;
}

Noeud* parse_document() {
    verifier(DOC_OPEN);
    Noeud* n = creer_noeud(DOC_OPEN);
    n->premier_fils = parse_contenu();
    verifier(DOC_CLOSE);
    return n;
}