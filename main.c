#include <stdio.h>
#include <stdlib.h>
#include "analyseur.h"
#include "rendu.h"

Noeud* parse_texte_enrichi();
void generer_rendu(Noeud* racine);

int main(int argc, char *argv[]) {
    if(argc != 2){
        fprintf(stderr, "Erreur de parametrage : Usage \n\t %s FICHIER.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialisation 
    amorcer(argv[1]);
    
    // lecture
    lire_jeton(); 

    //Analyseur qui va construire l'arbre
    Noeud* racine = parse_texte_enrichi();

    // AFFICHAGE
    if (mon_jeton == FIN_FICHIER) {
        printf("\n--- ANALYSE REUSSIE, GENERATION DU RENDU ---\n\n");
        generer_rendu(racine);
    } else {
        fprintf(stderr, "Erreur de syntaxe : on n'est pas arrive a la fin du fichier proprement.\n");
    }

    // Nettoyage
    terminer();

    return 0;
}