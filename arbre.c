#include "analyseur.h"

// Fonction pour créer un nouveau noeud dans l'arbre
Noeud* creer_noeud(t_jeton type) {
    Noeud* n= (Noeud*)malloc(sizeof(Noeud)); // demande de memoire
    if (n != NULL){

        // Initialisation des valeurs par défaut
        n->type = type;
        n->valeur[0]= '\0';
        n->premier_fils= NULL;
        n->frere_suivant = NULL;
    } else {
        // Arrêt si la mémoire est pleine
        fprintf(stderr, "Erreur : plus de memoire disponible.\n");
        exit(EXIT_FAILURE);
    }
    return n;
}