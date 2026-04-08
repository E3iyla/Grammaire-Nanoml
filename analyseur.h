// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>


// typedef enum {
//     DOC_OPEN, DOC_CLOSE,     // <document> , </document>
//     SEC_OPEN, SEC_CLOSE,     // <section> , </section>
//     ANN_OPEN, ANN_CLOSE,     // <annexe> , </annexe>
//     TITRE_OPEN, TITRE_CLOSE, // <titre> , </titre>
//     LISTE_OPEN, LISTE_CLOSE, // <liste> , </liste>
//     ITEM_OPEN, ITEM_CLOSE,   // <item> , </item>
//     BR,                      // <br/>
//     MOT,                     // Texte normal
//     FIN_FICHIER
// } Jeton;

// // Structure de l'Arbre N-aire (Premier fils, FrÃ¨re suivant)
// typedef struct Noeud {
//     Jeton type;
//     char valeur[256];              // Stocke le texte si c'est un MOT
//     struct Noeud* premier_fils;
//     struct Noeud* frere_suivant;
// } Noeud;

// // Variables globales 
// FILE *fichier;
// Jeton jeton_courant;
// char valeur_courante[256]; // Stocke temporairement le mot lu

#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <stdio.h>
#include "arbre.h"

extern FILE *fichier;
extern Jeton jeton_courant;
extern char valeur_courante[512];

void suivant();
void verifier(Jeton attendu);
void erreur(const char* message);
Noeud* creer_noeud(Jeton type);

// Fonctions de la grammaire
Noeud* parse_texte_enrichi();
Noeud* parse_document();
Noeud* parse_annexes();
Noeud* parse_contenu();
Noeud* parse_section();
Noeud* parse_liste();

#endif