#include "arbre.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Largeur imposée
#define LARGEUR_TOTALE 50

void afficher_noeud(Noeud* mon_noeud, int ma_largeur, int mon_indentation);
void afficher_contenu_ajuste(Noeud* mon_noeud, int largeur_dispo, int mon_indentation);
void dessiner_ligne(int ma_largeur, int mon_indentation);


// Fonction qui trace le bord haut ou bas d'une boîte 
void dessiner_ligne(int ma_largeur, int mon_indentation){
    for (int i = 0; i < mon_indentation; i++){
        printf(" ");
    }
    printf("+");
    for (int i = 0; i < ma_largeur - 2; i++) {
        printf("-");}
    printf("+\n");
}


// Fonction qui écrit le texte à l'intérieur des boîtes en gérant les retours à la ligne
void afficher_contenu_ajuste(Noeud* mon_noeud, int largeur_dispo, int mon_indentation) {
    int caracteres_ecrits = 0;
    Noeud* courant = mon_noeud;

    while (courant != NULL) {
        if (courant->type == MOT) {
            int longueur_mot = strlen(courant->valeur);
            
            // Si le mot est trop long on ferme la ligne et on en crée une nouvelle
            if (caracteres_ecrits > 0 && (caracteres_ecrits + longueur_mot + 1 > largeur_dispo - 4)) {
                for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                printf("|\n");
                caracteres_ecrits = 0;
            }

            // Début de ligne 
            if (caracteres_ecrits == 0) {
                for (int i = 0; i < mon_indentation; i++) printf(" ");
                printf("| ");
            } else {
                printf(" "); // Espace entre chaque mot
                caracteres_ecrits++;
            }

            printf("%s", courant->valeur);
            caracteres_ecrits += longueur_mot;
        } 
        else if (courant->type == BR) {
            // Un retour à la ligne manuel
            if (caracteres_ecrits == 0) { 
                for (int i = 0; i < mon_indentation; i++) printf(" "); 
                printf("| "); 
            }
            for  (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                printf("|\n");
            caracteres_ecrits = 0;
        }
        else if (courant->type == LISTE_OPEN) {
             if (caracteres_ecrits > 0) {
                 for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                 printf("|\n");
                 caracteres_ecrits = 0;
             }
             // On parcourt
             Noeud* iterateur = courant->premier_fils;
             while(iterateur != NULL) {
                 for (int i = 0; i < mon_indentation; i++) printf(" ");
                 printf("| # "); 
                 // On affiche l'intérieur de l'item avec plus d'indentation
                 afficher_contenu_ajuste(iterateur->premier_fils, largeur_dispo - 4, mon_indentation + 2);
                 iterateur = iterateur->frere_suivant;
             }
        }
        else if (courant->type == SEC_OPEN || courant->type == TITRE_OPEN || courant->type == ANN_OPEN) {
             // Une nouvelle sous-boite démarre on ferme la ligne courante
             if (caracteres_ecrits > 0) {
                 for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
                 printf("|\n");
                 caracteres_ecrits = 0;
             }
             // On appelle afficher_noeud pour dessiner
             afficher_noeud(courant, largeur_dispo - 2, mon_indentation + 1);
        }
        
        courant = courant->frere_suivant;}

    if (caracteres_ecrits > 0) {
        for (int i = caracteres_ecrits; i < largeur_dispo - 3; i++) printf(" ");
        printf("|\n");
    }
}


void afficher_noeud(Noeud* mon_noeud, int ma_largeur, int mon_indentation) {
    if (mon_noeud == NULL) return;
    
    // Si c'est un conteneur (document, section, annexe) on dessine une boite autour
    if (mon_noeud->type == DOC_OPEN || mon_noeud->type == SEC_OPEN || mon_noeud->type == ANN_OPEN) {
        dessiner_ligne(ma_largeur, mon_indentation);
        afficher_contenu_ajuste(mon_noeud->premier_fils, ma_largeur, mon_indentation);
        dessiner_ligne(ma_largeur, mon_indentation);
    } 
    // Si c'est un titre on le met en majuscules 
    else if (mon_noeud->type == TITRE_OPEN) {
        for (int i = 0; i < mon_indentation; i++) printf(" ");
        printf("| ");
        
        int car_titre = 0;
        Noeud* fils = mon_noeud->premier_fils;
        
        while(fils != NULL) {
            if(fils->type == MOT) {
                for(int j = 0; fils->valeur[j] != '\0'; j++) { 
                    putchar(toupper(fils->valeur[j])); 
                    car_titre++; 
                }
                putchar(' '); 
                car_titre++;
            }
            fils = fils->frere_suivant;}
        for (int i = car_titre; i < ma_largeur - 3; i++) printf(" ");
        printf("|\n");
    }
}


// Fonction principale
void generer_rendu(Noeud* racine) {
    Noeud* courant = racine;
    
    while (courant != NULL) {
        // On lance l'affichage à partir du premier nœud
        afficher_noeud(courant, LARGEUR_TOTALE, 0); 
        printf("\n");
        courant = courant->frere_suivant;
    }
}