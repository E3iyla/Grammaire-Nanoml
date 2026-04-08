#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rendu.h"

void afficher_noeud(Noeud* n, int largeur, int indentation);

void dessiner_ligne(int largeur, int indentation) {
    for (int i = 0; i < indentation; i++) printf(" ");
    printf("+");
    for (int i = 0; i < largeur - 2; i++) printf("-");
    printf("+\n");
}

void afficher_contenu_ajuste(Noeud* n, int largeur_dispo, int indentation) {
    int caracteres_ecrits = 0;
    Noeud* courant = n;

    while (courant) {
        if (courant->type == MOT) {
            int len = strlen(courant->valeur);
            
            // Si le mot ne rentre pas, on ferme la ligne et on passe à la suivante
            if (caracteres_ecrits > 0 && (caracteres_ecrits + len + 1 > largeur_dispo - 4)) {
                for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                printf("|\n");
                caracteres_ecrits = 0;
            }

            if (caracteres_ecrits == 0) {
                for (int i = 0; i < indentation; i++) printf(" ");
                printf("| ");
            } else {
                printf(" "); // Espace entre les mots
                caracteres_ecrits++;
            }

            printf("%s", courant->valeur);
            caracteres_ecrits += len;
        } 
        else if (courant->type == BR) {
            if (caracteres_ecrits == 0) { for (int i = 0; i < indentation; i++) printf(" "); printf("| "); }
            for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
            printf("|\n");
            caracteres_ecrits = 0;
        }
        else if (courant->type == LISTE_OPEN) {
             if (caracteres_ecrits > 0) {
                 for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                 printf("|\n");
                 caracteres_ecrits = 0;
             }
             Noeud* it = courant->premier_fils;
             while(it) {
                 for (int i = 0; i < indentation; i++) printf(" ");
                 printf("| # "); 
                 // Appel récursif pour le contenu de l'item
                 afficher_contenu_ajuste(it->premier_fils, largeur_dispo - 4, indentation + 2);
                 it = it->frere_suivant;
             }
        }
        else if (courant->type == SEC_OPEN || courant->type == TITRE_OPEN || courant->type == ANN_OPEN) {
             if (caracteres_ecrits > 0) {
                 for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                 printf("|\n");
                 caracteres_ecrits = 0;
             }
             // On décale l'indentation pour les blocs imbriqués
             afficher_noeud(courant, largeur_dispo - 2, indentation + 1);
        }
        courant = courant->frere_suivant;
    }

    // Fermeture de la dernière ligne si nécessaire
    if (caracteres_ecrits > 0) {
        for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
        printf("|\n");
    }
}

void afficher_noeud(Noeud* n, int largeur, int indentation) {
    if (!n) return;
    if (n->type == DOC_OPEN || n->type == SEC_OPEN || n->type == ANN_OPEN) {
        dessiner_ligne(largeur, indentation);
        afficher_contenu_ajuste(n->premier_fils, largeur, indentation);
        dessiner_ligne(largeur, indentation);
    } 
    else if (n->type == TITRE_OPEN) {
        for (int i = 0; i < indentation; i++) printf(" ");
        printf("| ");
        int car_titre = 0;
        Noeud* f = n->premier_fils;
        while(f) {
            if(f->type == MOT) {
                for(int j=0; f->valeur[j]; j++) { putchar(toupper(f->valeur[j])); car_titre++; }
                putchar(' '); car_titre++;
            }
            f = f->frere_suivant;
        }
        for (int i = car_titre; i < largeur - 3; i++) printf(" ");
        printf("|\n");
    }
}

void generer_rendu(Noeud* racine) {
    Noeud* courant = racine;
    while (courant != NULL) {
        afficher_noeud(courant, LARGEUR_TOTALE, 0); // Utilise la constante de rendu.h
        printf("\n");
        courant = courant->frere_suivant;
    }
}