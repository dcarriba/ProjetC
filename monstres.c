#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdprof.h"
#include "personnages.h"
#include "grid.h"
#include "monstres.h"

int monstre_len_nom(char *commande){
    /*renvoie le nombre de caracteres du nom du monstre*/
    int i;
    int len_nom = 0;
    for(i=1;i<strlen(commande);i++){
        if(commande[i]==','){ /*si on rencotre ',' on sait qu'on est arrive a la fin du nom, car ',' separe le nom de la force*/
            return len_nom;
        }
        len_nom++;
    }
    return len_nom;
}

char * extraire_monstre_nom(char *commande){
    /*renvoie le nom du monstre a partir de la commande*/
    int i;
    int len_nom = monstre_len_nom(commande);
    char *nom = stdprof_malloc((len_nom+1)*sizeof(char));
    for(i=1;i<len_nom+1;i++){
        nom[i-1]=commande[i];
    }
    nom[len_nom]='\0';
    return nom;
}

int extraire_monstre_force(char *commande){
    /*renvoie la force du monstre a partir de la commande*/
    int force = 0;
    int dec = 1;
    int i;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 1){ /*on commence apres avoir rencontre la premiere virgule*/
            if(commande[i]==','){ /*lorsqu'on rencontre la seconde virgule, on retourne la valeur de force*/
                return force;
            }
            if(commande[i]>='0' && commande[i]<='9'){
                force = force*dec+(commande[i]-'0');
                dec = 10;
            }
        } else {
            if(commande[i]==','){ /*si on rencontre la premiere virgule la variable commencer devient 1*/
                commencer++;
            }
        }
    }
    return -1;
}

int extraire_monstre_vie(char *commande){
    /*renvoie la vie du monstre a partir de la commande*/
    int vie = 0;
    int dec = 1;
    int i;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 2){ /*on commence apres avoir rencontre les deux virgules*/
            if(commande[i]=='>'){ /*lorsqu'on arrive a la fin on retourne la valeur de la vie*/
                return vie;
            }
            if(commande[i]>='0' && commande[i]<='9'){
                vie = vie*dec+(commande[i]-'0');
                dec = 10;
            }
        } else {
            if(commande[i]==','){ /*pour chaque virgule qu'on rencontre on augmente commencer de 1*/
                commencer++;
            }
        }
    }
    return -1;
}

monstre creation_monstre(char *commande){
    /*fonction qui cree le monstre*/
    monstre M;
    M.nom = extraire_monstre_nom(commande);
    M.force = extraire_monstre_force(commande);
    M.vie = extraire_monstre_vie(commande);
    M.x = -1;
    M.y = -1;
    return M;
}

void liberer_monstre(monstre M){
    /*libere la memoire occupe par le nom du monstre*/
    stdprof_free(M.nom);
}

ensemble_monstre creation_ensemble_monstre(){
    /*cree l'ensemble de monstre ou seront stocker tout les monstres du jeu*/
    ensemble_monstre E;
    int taille = 1;
    E.memoire = stdprof_malloc(taille*sizeof(monstre));
    E.taille = taille;
    E.n = 0;
    return E;
}

void liberer_ensemble_monstre(ensemble_monstre *E){
    /*libere l'ensemble de monstre ou sont stocker tout les monstres du jeu*/
    int i;
    for(i=0;i<E->n;i++){
        liberer_monstre(E->memoire[i]);
    }
    stdprof_free(E->memoire);
}

void placer_monstre(monstre *M, grid G, int x, int y){
    /*place un monstre sur la grille du jeu en (x,y)*/
    M->x = x;
    M->y = y;
    G[y+2][(x+1)*2]='@';
    printf("[!] Placement effectué de :\n");
    afficher_monstre(M);
}

void agrandir_ensemble_monstre(ensemble_monstre *E){
    /*si l'ensemble n'est pas assez grand, on l'agrandit pour pouvoir y stocker plus de monstres*/
    int i;
    monstre *ancienne_mem = E->memoire;
    monstre *nouv_mem = stdprof_malloc((E->taille)*2 * sizeof(monstre));
    for(i=0;i<(E->n);i++){
        nouv_mem[i]=ancienne_mem[i];
    }
    stdprof_free(E->memoire);
    E->memoire = nouv_mem;
    E->taille = (E->taille)*2;
}

void ajouter_monstre(ensemble_monstre *E, char *commande){
    /*ajoute un monstre au jeu, apres de le creer*/
    if(E->n == E->taille){ /*Si l'ensemble est complet, alors on l'agrandit*/
        agrandir_ensemble_monstre(E);
    }
    E->memoire[E->n] = creation_monstre(commande);
    (E->n)++;
}

int identifier_monstre(ensemble_monstre *E, grid G, int x, int y){
    /*identifie quel monstre se situe aux coordonnees (x,y)*/
    int i;
    for(i=0;i<E->n;i++){
        if(E->memoire[i].x == x && E->memoire[i].y == y){
            return i;
        }
    }
    return -1;
}

void supprimer_monstre(int id, ensemble_monstre *E, grid G){
    /*supprime un monstre du jeu*/
    int i;
    enlever(G,E->memoire[id].x,E->memoire[id].y);
    liberer_monstre(E->memoire[id]);
    for(i=id;i<(E->n)-1;i++){  /*apres avoir supprimer le monstre on avance tout les monstres stocke apres dans l'ensemble pour ne pas de laisser de trou dans l'ensemble de monstre*/
        E->memoire[i]=E->memoire[i+1];
    }
    E->n = E->n - 1;
}

void afficher_monstre(monstre *M){
    /*affiche les stats du monstre*/
    printf("[Monstre]\nNom : %s\n",M->nom);
    printf("Coordonnees : (%d,%d)\n",M->x,M->y);
    printf("Force : %d\n",M->force);
    printf("Vie : %d\n\n",M->vie);
}

void procede_monstre(grid G, int *x, int *y, ensemble_monstre *E, char *commande){
    /*fonction qui s'occupe du placement du monstre*/
    if(place_sur_grille(G,*x,*y)){ /*Si il y a de la place en (x,y) alors*/
        ajouter_monstre(E,commande); /*on stocke le monstre dans la memoire*/
        placer_monstre(&(E->memoire[(E->n)-1]),G,*x,*y); /*on place le monstre en (x,y)*/
    } else if (coords_invalides(*x,*y)){ /*Sinon si ce n'est pas possible parceque les coordonnees sont erronees Alors envoyer le Warning suivant, et ne pas stocker le monstre dans la memoire (et ne pas le placer sur la grille)*/
        fprintf(stderr,"[WARNING] Attention les coordonnées sont erronées. Il doivent être dans la limite du plan de jeu.\n\n");
    } else { /*Sinon envoyer le Warning suivant, et ne pas stocker le monstre dans la memoire (et ne pas le placer sur la grille)*/
        fprintf(stderr,"[WARNING] Impossible de placer le monstre. Autre chose est déjà présente aux coordonnées (%d,%d).\n\n",*x,*y);
    }
    *x = -1; /*On a plus besoins des coordonnees*/
    *y = -1; /*On les mets donc a -1*/
}
