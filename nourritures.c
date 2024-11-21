#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdprof.h"
#include "personnages.h"
#include "grid.h"
#include "nourritures.h"

int nourriture_len_nom(char *commande){
    /*renvoie le nombre de caracteres du nom de la nourriture*/
    int i;
    int len_nom = 0;
    for(i=1;i<strlen(commande);i++){
        if(commande[i]==','){ /*si on rencotre ',' on sait qu'on est arrive a la fin du nom, car ',' separe le nom de la valeur*/
            return len_nom;
        }
        len_nom++;
    }
    return len_nom;
}

char * extraire_nourriture_nom(char *commande){
    /*renvoie le nom de la nourriture a partir de la commande*/
    int i;
    int len_nom = nourriture_len_nom(commande);
    char *nom = stdprof_malloc((len_nom+1)*sizeof(char));
    for(i=1;i<len_nom+1;i++){
        nom[i-1]=commande[i];
    }
    nom[len_nom]='\0';
    return nom;
}

int extraire_nourriture_valeur(char *commande){
    /*renvoie la valeur de la nourriture a partir de la commande*/
    int valeur = 0;
    int dec = 1;
    int i;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 1){ /*on commence apres avoir rencontre la premiere virgule*/
            if(commande[i]==','){ /*lorsqu'on rencontre la seconde virgule, on retourne la valeur*/
                return valeur;
            }
            if(commande[i]>='0' && commande[i]<='9'){
                valeur = (valeur*dec)+(commande[i]-'0');
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

int nourriture_len_description(char *commande){
    /*renvoie le nombre de caracteres de la description de la nourriture*/
    int i;
    int n = 0;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 1){ /*on commence apres avoir rencontre le premier guillemet*/
            if(commande[i]=='\"'){ /*lorsqu'on rencontre le second guillemet, on retourne la taille de la description*/
                return n;
            }
            n++;
        } else {
            if(commande[i]=='\"'){ /*si on rencontre le premier guillemet la variable commencer devient 1*/
                commencer++;
            }
        }
    }
    return -1;
}

char * extraire_nourriture_description(char *commande){
    /*renvoie la description de la nourriture a partir de la commande*/
    int len_description = nourriture_len_description(commande);
    char *nom = stdprof_malloc((len_description+1)*sizeof(char));
    int i;
    int j = 0;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){ 
        if(commencer == 1){ /*on commence apres avoir rencontre le premier guillemet*/
            if(commande[i]=='\"'){ /*lorsqu'on rencontre le second guillemet, on retourne la description de la nourriture*/
                nom[j]='\0';
                return nom;
            }
            nom[j]=commande[i];
            j++;
        } else {
            if(commande[i]=='\"'){ /*si on rencontre le premier guillemet la variable commencer devient 1*/
                commencer++;
            }
        }
    }
    return "";
}

nourriture creation_nourriture(char *commande){
    /*fonction qui cree la nourriture*/
    nourriture N;
    N.nom = extraire_nourriture_nom(commande);
    N.valeur = extraire_nourriture_valeur(commande);
    N.description = extraire_nourriture_description(commande);
    N.x = -1;
    N.y = -1;
    return N;
}

void liberer_nourriture(nourriture N){
    /*libere la memoire occupe par le nom et par la description de la nourriture*/
    stdprof_free(N.nom);
    stdprof_free(N.description);
}

ensemble_nourriture creation_ensemble_nourriture(){
    /*cree l'ensemble de nourriture ou seront stocker toutes les nourritures du jeu*/
    ensemble_nourriture E;
    int taille = 1;
    E.memoire = stdprof_malloc(taille*sizeof(nourriture));
    E.taille = taille;
    E.n = 0;
    return E;
}

void liberer_ensemble_nourriture(ensemble_nourriture *E){
    /*libere l'ensemble de nourriture ou sont stocker toutes les nourritures du jeu*/
    int i;
    for(i=0;i<E->n;i++){
        liberer_nourriture(E->memoire[i]);
    }
    stdprof_free(E->memoire);
}

void placer_nourriture(nourriture *N, grid G, int x, int y){
    /*place une nourriture sur la grille du jeu en (x,y)*/
    N->x = x;
    N->y = y;
    G[y+2][(x+1)*2]='*';
    printf("[!] Placement effectué de :\n");
    afficher_nourriture(N);
}

void agrandir_ensemble_nourriture(ensemble_nourriture *E){
    /*si l'ensemble n'est pas assez grand, on l'agrandit pour pouvoir stocker plus de nourritures*/
    int i;
    nourriture *ancienne_mem = E->memoire;
    nourriture *nouv_mem = stdprof_malloc((E->taille)*2 * sizeof(nourriture));
    for(i=0;i<(E->n);i++){
        nouv_mem[i]=ancienne_mem[i];
    }
    stdprof_free(E->memoire);
    E->memoire = nouv_mem;
    E->taille = (E->taille)*2;
}

void ajouter_nourriture(ensemble_nourriture *E, char *commande){
    /*ajoute une nourriture au jeu, apres de le creer*/
    if(E->n == E->taille){ /*Si l'ensemble est complet, alors on l'agrandit*/
        agrandir_ensemble_nourriture(E);
    }
    E->memoire[E->n] = creation_nourriture(commande);
    (E->n)++;
}

int identifier_nourriture(ensemble_nourriture *E, grid G, int x, int y){
    /*identifie quelle nourriture se situe aux coordonnees (x,y)*/
    int i;
    for(i=0;i<E->n;i++){
        if(E->memoire[i].x == x && E->memoire[i].y == y){
            return i;
        }
    }
    return -1;
}

void supprimer_nourriture(int id, ensemble_nourriture *E, grid G){
    /*supprime une nourriture du jeu*/
    int i;
    enlever(G,E->memoire[id].x,E->memoire[id].y);
    liberer_nourriture(E->memoire[id]);
    for(i=id;i<(E->n)-1;i++){ /*apres avoir supprimer la nourriture on avance tout les nourriture stocke apres dans l'ensemble pour ne pas de laisser de trou dans l'ensemble de nourriture*/
        E->memoire[i]=E->memoire[i+1];
    }
    E->n = E->n - 1;
}

void afficher_nourriture(nourriture *N){
    /*affiche les stats de la nourriture*/
    printf("[Nourriture]\nNom : %s\n",N->nom);
    printf("Valeur : %d\n",N->valeur);
    printf("Description : %s\n",N->description);
    printf("Coordonnees : (%d,%d)\n\n",N->x,N->y);
}

void procede_nourriture(grid G, int *x, int *y, ensemble_nourriture *E, char *commande){
    /*fonction qui s'occupe du placement de la nourriture*/
    if(place_sur_grille(G,*x,*y)){ /*Si il y a de la place en (x,y) alors*/
        ajouter_nourriture(E,commande); /*on stocke la nourriture dans la memoire*/
        placer_nourriture(&(E->memoire[(E->n)-1]),G,*x,*y); /*on place la nourriture en (x,y)*/
    } else if (coords_invalides(*x,*y)){ /*Sinon si ce n'est pas possible parceque les coordonnees sont erronees Alors envoyer le Warning suivant, et ne pas stocker la nourriture dans la memoire (et ne pas le placer sur la grille)*/
        fprintf(stderr,"[WARNING] Attention les coordonnées sont erronées. Il doivent être dans la limite du plan de jeu.\n\n");
    } else { /*Sinon envoyer le Warning suivant, et ne pas stocker la nourriture dans la memoire (et ne pas le placer sur la grille)*/
        fprintf(stderr,"[WARNING] Impossible de placer le nourriture. Autre chose est déjà présente aux coordonnées (%d,%d).\n\n",*x,*y);
    }
    *x = -1; /*On a plus besoins des coordonnees*/
    *y = -1; /*On les mets donc a -1*/
}