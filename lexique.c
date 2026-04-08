#include "analyseur.h"
#include <string.h>
#include <ctype.h>


char mon_caractere;
FILE* mon_fichier;
t_jeton mon_jeton;          
char mon_mot[512];          


// Fonctions de lecture de base

void lire_caractere() {
    if(fscanf(mon_fichier, "%c", &mon_caractere) != 1) {
        if(!feof(mon_fichier)) {
            fprintf(stderr, "Erreur de lecture.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (feof(mon_fichier)) {
        mon_caractere = EOF;
    }
   
}

int est_en_fin() {
    return feof(mon_fichier);
}

void amorcer(char* nom_fichier) {
    mon_fichier = fopen(nom_fichier, "r");
    if(mon_fichier == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    lire_caractere(); // On lit le tout premier caractère pour amorcer la pompe
}

void terminer() {
    if(fclose(mon_fichier) != 0) {
        fprintf(stderr, "Erreur de fermeture du fichier\n");
    }
}

void passer_espaces() {
    // On ignore les espaces sauts de ligne
    while (mon_caractere == ' ' || mon_caractere == '\t' || mon_caractere == '\n' || mon_caractere == '\r') {
        lire_caractere();
    }
}


// Lit le prochain jeton (balise ou mot)
void lire_jeton() {
    passer_espaces();

    if (mon_caractere == EOF) {
        mon_jeton = FIN_FICHIER;
        return;
    }

    // cas d'une balise
    if (mon_caractere == '<') {
        char buffer[100];
        int i = 0;
        
        buffer[i++] = mon_caractere; // On stocke le '<'
        lire_caractere();

        //lit tout jusqu'à fin de la balise
        while (mon_caractere != '>' && mon_caractere != EOF) {
            buffer[i++] = mon_caractere;
            lire_caractere();
        }
        
        buffer[i++] = '>'; // stocke le '>'
        buffer[i] = '\0';  // marque la fin de la chaine de caractères
        
        lire_caractere(); 

        // identifie quelle balise
        if (strcmp(buffer, "<document>") == 0) mon_jeton = DOC_OPEN;
        else if (strcmp(buffer, "</document>") == 0) mon_jeton = DOC_CLOSE;
        else if (strcmp(buffer, "<section>") == 0) mon_jeton = SEC_OPEN;
        else if (strcmp(buffer, "</section>") == 0) mon_jeton = SEC_CLOSE;
        else if (strcmp(buffer, "<titre>") == 0) mon_jeton = TITRE_OPEN;
        else if (strcmp(buffer, "</titre>") == 0) mon_jeton = TITRE_CLOSE;
        else if (strcmp(buffer, "<annexe>") == 0) mon_jeton = ANN_OPEN;
        else if (strcmp(buffer, "</annexe>") == 0) mon_jeton = ANN_CLOSE;
        else if (strcmp(buffer, "<liste>") == 0) mon_jeton = LISTE_OPEN;
        else if (strcmp(buffer, "</liste>") == 0) mon_jeton = LISTE_CLOSE;
        else if (strcmp(buffer, "<item>") == 0) mon_jeton = ITEM_OPEN;
        else if (strcmp(buffer, "</item>") == 0) mon_jeton = ITEM_CLOSE;
        else if (strcmp(buffer, "<br/>") == 0) mon_jeton = BR;
        else {
            // Si la balise n'est pas reconnue alors est comme un mot
            mon_jeton = MOT; 
            strcpy(mon_mot, buffer);
        }
    } 
    // cas d un mot normal
    else {
        int i = 0;
       
        while (mon_caractere != EOF && mon_caractere != ' ' && mon_caractere != '\t' && 
               mon_caractere != '\n' && mon_caractere != '\r' && mon_caractere != '<') {
            if (i < 511) { 
                mon_mot[i++] = mon_caractere;
            }
            lire_caractere();
        }
        mon_mot[i] = '\0'; // Fin de la chaine
        mon_jeton = MOT;
    }
}

// Vérifie le jeton courant et passe au suivant
void consommer_jeton(t_jeton attendu) {
    if (mon_jeton == attendu) {
        lire_jeton();
    } else {
        fprintf(stderr, "Erreur de syntaxe : le jeton lu ne correspond pas a ce qui etait attendu.\n");
        exit(EXIT_FAILURE);
    }
}