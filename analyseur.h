#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

// Nos variables globales (partagées partout)
extern char mon_caractere;
extern FILE* mon_fichier;
extern t_jeton mon_jeton;
extern char mon_mot[512];

// Prototypes pour démarrer et lire
void amorcer(char* nom_fichier);
void terminer();
void lire_jeton();
void consommer_jeton(t_jeton attendu);

// Prototype principal de l'analyseur
Noeud* parse_texte_enrichi();

#endif