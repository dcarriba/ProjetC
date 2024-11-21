#ifndef TYPESMONSTRES_H
#define TYPESMONSTRES_H

typedef struct monstre_structure {
    char *nom;
    int force;
    int vie;
    int x;
    int y;
} monstre;

typedef struct ensemble_monstre_struct {
    monstre *memoire;
    int taille;
    int n;
} ensemble_monstre;

#endif
#include "grid.h"

int monstre_len_nom(char *commande);
int extraire_monstre_force(char *commande);
int extraire_monstre_vie(char *commande);
monstre creation_monstre(char *commande);
void liberer_monstre(monstre M);
ensemble_monstre creation_ensemble_monstre();
void liberer_ensemble_monstre(ensemble_monstre *E);
void placer_monstre(monstre *M, grid G, int x, int y);
void agrandir_ensemble_monstre(ensemble_monstre *E);
void ajouter_monstre(ensemble_monstre *E, char *commande);
int identifier_monstre(ensemble_monstre *E, grid G, int x, int y);
void supprimer_monstre(int id, ensemble_monstre *E, grid G);
void afficher_monstre(monstre *M);
void procede_monstre(grid G, int *x, int *y, ensemble_monstre *E, char *commande);
