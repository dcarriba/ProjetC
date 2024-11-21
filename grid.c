#include <stdio.h>
#include <stdlib.h>
#include "stdprof.h"
#include "grid.h"

grid initialisation(void){ 
    /*on initialise la grille du jeu*/
    int i;
    int j;
    char chiffre = '0';
    char lettre = 'A';
    int lignes = 14;
    int colonnes = 24;
    grid G = stdprof_malloc(lignes*sizeof(char*));
    for(i=0;i<lignes;i++){ /*creation de chaque ligne*/
        G[i]=stdprof_malloc(colonnes*sizeof(char));
        if(i==0){ /*numerotation en haut de la grille*/
            for(j=0;j<colonnes;j++){ 
                if(j%2==0 && j!=0){
                    if(chiffre<='9'){
                        G[i][j]=chiffre;
                        chiffre++;
                    } else{
                        G[i][j]=lettre;
                        lettre++;
                    }
                } else {
                    G[i][j] = ' ';
                }
            }
            chiffre = '0';
            lettre = 'A';
        } else if(i==1 || i==lignes-1){ /*bord superieur et inferieur de la grille*/
            for(j=0;j<colonnes;j++){
                if(j==0){
                    G[i][j] = ' ';
                } else if(j%2==0 && j!=0){
                    G[i][j]='-';
                } else {
                    G[i][j] = '+';
                }
            }
        } else {
            for(j=0;j<colonnes;j++){
                if(j==0){ /*numerotation a droite de la grille*/
                    if(i>=2 && i<=lignes-2){ 
                        if(chiffre<='9'){
                            G[i][j]=chiffre;
                            chiffre++;
                        } else{
                            G[i][j]=lettre;
                            lettre++;
                        }
                    } else {
                        G[i][j] = ' ';
                    }
                } else if(j==1 || j==colonnes-1){ /*bord droit et gauche de la grille*/
                    G[i][j]='|';
                } else { /*le reste est vide*/
                    G[i][j]=' ';
                }
            }
        }
    }
    return G;
}

void liberer_grid(grid G){
    /*on libere la grille du jeu*/
    int i;
    int lignes = 14;
    for(i=0;i<lignes;i++){ /*on libere chaque ligne induviduellement*/
        stdprof_free(G[i]);
    }
    stdprof_free(G); /*on libere le tout*/
}

void affichage(grid G){
    /*on affiche la grille du jeu*/
    int i;
    int j;
    int lignes = 14;
    int colonnes = 24;
    for(i=0;i<lignes;i++){
        for(j=0;j<colonnes;j++){
            printf("%c",G[i][j]);
        }
        printf("\n");
    }
}

void enlever(grid G, int x, int y){
    /*remet un case vide en (x,y)*/
    G[y+2][(x+1)*2]=' ';
}

int placement_possible(grid G, int x, int y){
    /*renvoie True si Rahan peut etre placer sur cette case*/
    return (x>=0 && x<=10 && y>=0 && y<=10 && (G[y+2][(x+1)*2]==' ' || G[y+2][(x+1)*2]=='@' || G[y+2][(x+1)*2]=='*' || G[y+2][(x+1)*2]=='!'));
}

int place_sur_grille(grid G, int x, int y){
    /*renvoie True si il y a de place sur une case pour y placer un rocher/monstre/nourriture/equipement*/
    return (x>=0 && x<=10 && y>=0 && y<=10 && G[y+2][(x+1)*2]==' ');
}

int coords_invalides(int x, int y){
    /*renvoie True si les coordonnees x et y sont en dehors de la grille 10*10 */
    return (x<=0 || x>=10 || y<=0 || y>=10);
}

void placer_rocher(grid G, int x, int y){
    /*place un rocher sur la grille en (x,y)*/
    G[y+2][(x+1)*2]='#';
    printf("[!] Placement effectué de :\n[Rocher]\nCoordonnees : (%d,%d)\n\n",x,y);
}

void procede_rocher(grid G, int *x, int *y){
    /*fonction qui s'occupe du placement du rocher*/
    if(place_sur_grille(G,*x,*y)){ /*Si il y a de la place en (x,y)*/
        placer_rocher(G,*x,*y); /*Alors on y place le rocher*/
    } else if (coords_invalides(*x,*y)){ /*Sinon si ce n'est pas possible parceque les coordonnees sont erronees Alors envoyer le Warning suivant, et ne pas placer le rocher*/
        fprintf(stderr,"[WARNING] Attention les coordonnées sont erronées. Il doivent être dans la limite du plan de jeu.\n\n");
    } else { /*Sinon envoyer le Warning suivant, et ne pas placer le rocher*/
        fprintf(stderr,"[WARNING] Impossible de placer le rocher. Autre chose est déjà présente aux coordonnées (%d,%d).\n\n",*x,*y);
    }
    *x = -1; /*On a plus besoins des coordonnees*/
    *y = -1; /*On les mets donc a -1*/
}

int monstre_sur_grille(grid G, int x, int y){
    /*renvoie True si il y a un monstre en (x,y)*/
    return  G[y+2][(x+1)*2]=='@';
}

int nourriture_sur_grille(grid G, int x, int y){
    /*renvoie True si il y a de la nourriture en (x,y)*/
    return  G[y+2][(x+1)*2]=='*';
}

int equipement_sur_grille(grid G, int x, int y){
    /*renvoie True si il y a un equipement en (x,y)*/
    return  G[y+2][(x+1)*2]=='!';
}

int rocher_sur_grille(grid G, int x, int y){
    /*renvoie True si il y a un rocher en (x,y)*/
    return  G[y+2][(x+1)*2]=='#';
}



