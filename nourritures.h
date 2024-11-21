#ifndef TYPESNOURRITURES_H
#define TYPESNOURRITURES_H

typedef struct nourriture_structure {
    char *nom;
    int valeur;
    char *description;
    int x;
    int y;
} nourriture;

typedef struct ensemble_nourriture_struct {
    nourriture *memoire;
    int taille;
    int n;
} ensemble_nourriture;

#endif
#include "grid.h"

int nourriture_len_nom(char *commande);
char * extraire_nourriture_nom(char *commande);
int extraire_nourriture_valeur(char *commande);
int nourriture_len_description(char *commande);
char * extraire_nourriture_description(char *commande);
nourriture creation_nourriture(char *commande);
void liberer_nourriture(nourriture N);
ensemble_nourriture creation_ensemble_nourriture();
void liberer_ensemble_nourriture(ensemble_nourriture *E);
void placer_nourriture(nourriture *N, grid G, int x, int y);
void agrandir_ensemble_nourriture(ensemble_nourriture *E);
void ajouter_nourriture(ensemble_nourriture *E, char *commande);
int identifier_nourriture(ensemble_nourriture *E, grid G, int x, int y);
void supprimer_nourriture(int id, ensemble_nourriture *E, grid G);
void afficher_nourriture(nourriture *N);
void procede_nourriture(grid G, int *x, int *y, ensemble_nourriture *E, char *commande);
