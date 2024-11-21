#ifndef TYPESEQUIPEMENTS_H
#define TYPESEQUIPEMENTS_H

typedef enum classe_equipement_enumeration {
    chaussures,
    protections,
    armes
} classe_equipement;

typedef struct equipement_structure {
    char *nom;
    char attribut;
    int valeur;
    classe_equipement classe;
    int x;
    int y;
} equipement;

typedef struct ensemble_equipement_struct {
    equipement *memoire;
    int taille;
    int n;
} ensemble_equipement;

#endif
#include "grid.h"

int equipement_len_nom(char *commande);
char * extraire_equipement_nom(char *commande);
char extraire_equipement_attribut(char *commande);
int extraire_equipement_valeur(char *commande);
int equipement_len_classe(char *commande);
int extraire_equipement_classe(char *commande);
equipement creation_equipement(char *commande);
void liberer_equipement(equipement E);
ensemble_equipement creation_ensemble_equipement();
void liberer_ensemble_equipement(ensemble_equipement *E);
void liberer_ensemble_equipement_rahan(ensemble_equipement *E);
void placer_equipement(equipement *E, grid G, int x, int y);
void agrandir_ensemble_equipement(ensemble_equipement *E);
void ajouter_equipement(ensemble_equipement *E, char *commande);
int identifier_equipement(ensemble_equipement *E, grid G, int x, int y);
void supprimer_equipement(int id, ensemble_equipement *E, grid G);
char * equipement_nom_vide(void);
equipement creation_equipement_vide(int c);
void initialiser_equipement_rahan_vide(ensemble_equipement *E);
void afficher_equipement(equipement *E);
void afficher_equipements_rahan(equipement *E);
void afficher_tout_equipements_rahan(ensemble_equipement *E);
void procede_equipement(grid G, int *x, int *y, ensemble_equipement *E, char *commande);
