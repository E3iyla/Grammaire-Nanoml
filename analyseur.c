#include "analyseur.h"
#include <string.h>

// Déclaration de la fonction venant de arbre.c
Noeud* creer_noeud(t_jeton type);

// Prototypes locaux
Noeud* parse_document();
Noeud* parse_annexes();
Noeud* parse_contenu();
Noeud* parse_items();

// Point de départ de l'analyse
Noeud* parse_texte_enrichi() {
    //  Lit le document principal
    Noeud* racine = parse_document();

    //Ajoute les annexes à côté (en tant que frère)
    if (mon_jeton == ANN_OPEN) {
        racine->frere_suivant = parse_annexes();
    }
    return racine;
}

// Analyse de <document>
Noeud* parse_document() {
    consommer_jeton(DOC_OPEN);          // <document>
    Noeud* n = creer_noeud(DOC_OPEN);
         n->premier_fils = parse_contenu();  // Descend pour lire le contenu
    
    consommer_jeton(DOC_CLOSE);         // </document>
    return n;
}

// Analyse de <annexe>
Noeud* parse_annexes() {
    if (mon_jeton == ANN_OPEN) {
        consommer_jeton(ANN_OPEN);          // <annexe>
        Noeud* n = creer_noeud(ANN_OPEN);
        
        n->premier_fils = parse_contenu();
        
        consommer_jeton(ANN_CLOSE);         // </annexe>

        // Passe à l'annexe suivante s'il y en a une
        n->frere_suivant = parse_annexes();
        return n;
    }
    return NULL;
}

// Analyse du contenu général
Noeud* parse_contenu() {
    // Vérifie si le jeton est autorisé dans le contenu
    if (mon_jeton == MOT || mon_jeton == SEC_OPEN || 
        mon_jeton == TITRE_OPEN || mon_jeton == BR || mon_jeton == LISTE_OPEN) {
        
        Noeud* n = NULL;
        
        if (mon_jeton == MOT) {
            n = creer_noeud(MOT);
            strcpy(n->valeur, mon_mot); // Copie le texte du mot
            lire_jeton();
        } 
        else if (mon_jeton == BR) {
            n = creer_noeud(BR);
            lire_jeton();
        } 
        else if  (mon_jeton == SEC_OPEN){
            consommer_jeton(SEC_OPEN);
            n =  creer_noeud(SEC_OPEN);
            n->premier_fils = parse_contenu();
            consommer_jeton(SEC_CLOSE);
        } 
        else if (mon_jeton == TITRE_OPEN){
            consommer_jeton(TITRE_OPEN);
            n= creer_noeud(TITRE_OPEN);
            n->premier_fils = parse_contenu();
            consommer_jeton(TITRE_CLOSE);
        } 
        else if (mon_jeton == LISTE_OPEN){
            consommer_jeton(LISTE_OPEN);
            n =creer_noeud(LISTE_OPEN);
            n->premier_fils = parse_items();
            consommer_jeton(LISTE_CLOSE);
        }
        
        // Lit la suite du contenu au même niveau
        if (n != NULL) {
            n->frere_suivant = parse_contenu();
        }
        return n;
    }
    return NULL;
}

Noeud* parse_items() {
    if (mon_jeton == ITEM_OPEN) {
        consommer_jeton(ITEM_OPEN);          // <item>
        Noeud* n = creer_noeud(ITEM_OPEN);
        
        n->premier_fils = parse_contenu();
        
        consommer_jeton(ITEM_CLOSE);         // </item>

        // Passe au prochain item de la liste
        n->frere_suivant = parse_items();
        return n;
    }
    return NULL;
}