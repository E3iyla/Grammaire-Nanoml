#include <stdio.h>
#include "analyseur.h"
#include "rendu.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s fichier.txt\n", argv[0]);
        return 1;
    }
    fichier = fopen(argv[1], "r");
    if (!fichier) return 1;

    suivant(); // Lit le premier jeton
    Noeud* racine = parse_texte_enrichi(); // Nouvelle fonction racine

    if (jeton_courant == FIN_FICHIER) {
        generer_rendu(racine);
    } else {
        printf("Erreur de syntaxe : jeton inattendu en fin de fichier.\n");
    }

    fclose(fichier);
    return 0;
}