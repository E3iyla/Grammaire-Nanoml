#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "analyseur.h"

// Définition des variables globales (requises par analyseur.h)
Jeton jeton_courant;
char valeur_courante[512];
FILE *fichier = NULL;

// Lit le prochain élément du fichier
void suivant() {
    int c = fgetc(fichier);
    while (c != EOF && isspace(c)) c = fgetc(fichier); // Ignore les espaces

    if (c == EOF) {
        jeton_courant = FIN_FICHIER;
        return;
    }

    if (c == '<') {
        char buffer[100];
        int i = 0;
        buffer[i++] = c;
        while ((c = fgetc(fichier)) != '>' && c != EOF) buffer[i++] = c;
        buffer[i++] = '>';
        buffer[i] = '\0';

        // Identification des balises
        if (strcmp(buffer, "<document>") == 0) jeton_courant = DOC_OPEN;
        else if (strcmp(buffer, "</document>") == 0) jeton_courant = DOC_CLOSE;
        else if (strcmp(buffer, "<section>") == 0) jeton_courant = SEC_OPEN;
        else if (strcmp(buffer, "</section>") == 0) jeton_courant = SEC_CLOSE;
        else if (strcmp(buffer, "<titre>") == 0) jeton_courant = TITRE_OPEN;
        else if (strcmp(buffer, "</titre>") == 0) jeton_courant = TITRE_CLOSE;
        else if (strcmp(buffer, "<annexe>") == 0) jeton_courant = ANN_OPEN;
        else if (strcmp(buffer, "</annexe>") == 0) jeton_courant = ANN_CLOSE;
        else if (strcmp(buffer, "<liste>") == 0) jeton_courant = LISTE_OPEN;
        else if (strcmp(buffer, "</liste>") == 0) jeton_courant = LISTE_CLOSE;
        else if (strcmp(buffer, "<item>") == 0) jeton_courant = ITEM_OPEN;
        else if (strcmp(buffer, "</item>") == 0) jeton_courant = ITEM_CLOSE;
        else if (strcmp(buffer, "<br/>") == 0) jeton_courant = BR;
        else jeton_courant = MOT; 
    } else {
        int i = 0;
        valeur_courante[i++] = c;
        while ((c = fgetc(fichier)) != EOF && !isspace(c) && c != '<') {
            if (i < 511) valeur_courante[i++] = c;
        }
        valeur_courante[i] = '\0';
        if (c == '<') ungetc(c, fichier); // Repose le début de la balise
        jeton_courant = MOT;
    }
}

// Vérifie si le jeton est correct
void verifier(Jeton attendu) {
    if (jeton_courant == attendu) {
        suivant();
    } else {
        printf("Erreur : attendu %d, recu %d\n", attendu, jeton_courant);
    }
}