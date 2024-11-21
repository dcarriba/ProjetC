#ifndef TYPESGRID_H
#define TYPESGRID_H

typedef char **grid;

#endif

grid initialisation(void);
void liberer_grid(grid G);
void affichage(grid G);
void enlever(grid G, int x, int y);
int placement_possible(grid G, int x, int y);
int place_sur_grille(grid G, int x, int y);
int coords_invalides(int x, int y);
void placer_rocher(grid G, int x, int y);
void procede_rocher(grid G, int *x, int *y);
int monstre_sur_grille(grid G, int x, int y);
int nourriture_sur_grille(grid G, int x, int y);
int equipement_sur_grille(grid G, int x, int y);
int rocher_sur_grille(grid G, int x, int y);
