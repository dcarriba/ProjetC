#include "personnages.h"
#include "grid.h"
#include "monstres.h"

int commande_debut_erronee(char *commande);
int commande_de_mouvement(char *commande);
int commande_de_vision(char *commande);
int commande_invocation(char *commande);
int commande_rocher(char *commande);
int commande_coord_abs(char *commande);
int commande_coord_rel_demiurge(char *commande);
int commande_coord_rel_hero(char *commande);
int recuperer_coord(int i, char *commande);
void save_coord_abs(char *commande, int *x, int *y);
void save_coord_rel_demiurge(char *commande, int *x, int *y, demiurge *D);
void save_coord_rel_hero(char *commande, int *x, int *y, hero *H);
int commande_monstre(char *commande);
int commande_equipement(char *commande);
int commande_nourriture(char *commande);
int commande_trier(char *commande);
int commande_ia(char *commande);
int commande_de_fin(char *commande);
