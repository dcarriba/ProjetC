#ifndef TYPESPERSONNAGES_H
#define TYPESPERSONNAGES_H

typedef struct hero_structure {
    char *nom;
    int x;
    int y;
    int pts_vie;
    int sante;
    int force;
    int vitesse;
} hero;

typedef struct demiurge_structure {
    char nom;
    int x;
    int y;
} demiurge;

#endif
#include "monstres.h"
#include "nourritures.h"
#include "equipements.h"
#include "grid.h"

hero creation_rahan(void);
demiurge creation_olivier(void);
int placement_possible(grid G, int x, int y);
void placer_demiurge(demiurge *D, grid G, int x, int y);
void placer_hero(hero *H, grid G, int x, int y);
void combat_hero_monstre(hero *H, int id, ensemble_monstre *EnsM, grid G);
void manger_hero_nourriture(hero *H, int id, ensemble_nourriture *EnsN, grid G);
void equipper_hero_equipement(hero *H, int id, ensemble_equipement *EnsE, grid G, ensemble_equipement *EnsE_rahan);
void bouger(hero *H, int X, int Y, grid G, ensemble_monstre *EnsM, ensemble_nourriture *EnsN, ensemble_equipement *EnsE, ensemble_equipement *EnsE_rahan);
void deplacement(hero *H, char C, grid G, ensemble_monstre *EnsM, ensemble_nourriture *EnsN, ensemble_equipement *EnsE, ensemble_equipement *EnsE_rahan);
int ia_trouve_bonus_haut(grid G, int x, int y);
int ia_trouve_bonus_droite(grid G, int x, int y);
int ia_trouve_bonus_bas(grid G, int x, int y);
int ia_trouve_bonus_gauche(grid G, int x, int y);
int ia_trouve_malus_haut(grid G, int x, int y);
int ia_trouve_malus_droite(grid G, int x, int y);
int ia_trouve_malus_bas(grid G, int x, int y);
int ia_trouve_malus_gauche(grid G, int x, int y);
void ivoire_albe(hero *H, grid G, ensemble_monstre *EnsM, ensemble_nourriture *EnsN, ensemble_equipement *EnsE, ensemble_equipement *EnsE_rahan);
void afficher_stats(hero *H);
