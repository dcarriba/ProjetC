#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdprof.h"
#include "personnages.h"
#include "grid.h"
#include "equipements.h"

int equipement_len_nom(char *commande){
    /*renvoie le nombre de caracteres du nom de l'equipement*/
    int i;
    int len_nom = 0;
    for(i=1;i<strlen(commande);i++){
        if(commande[i]==','){ /*si on rencotre ',' on sait qu'on est arrive a la fin du nom, car ',' separe le nom de l'attribut*/
            return len_nom;
        }
        len_nom++;
    }
    return len_nom;
}

char * extraire_equipement_nom(char *commande){
    /*renvoie le nom de l'equipement a partir de la commande*/
    int i;
    int len_nom = equipement_len_nom(commande);
    char *nom = stdprof_malloc((len_nom+1)*sizeof(char));
    for(i=1;i<len_nom+1;i++){
        nom[i-1]=commande[i];

    }
    nom[len_nom]='\0';
    return nom;
}

char extraire_equipement_attribut(char *commande){
    /*renvoie l'attribut de l'equipement a partir de la commande*/
    int i;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 1){ /*on commence apres avoir rencontre la premiere virgule*/
            if(commande[i]=='V' || commande[i]=='P' || commande[i]=='F'){ /*si on a trouve l'attribut, on le retourne*/
                return commande[i];
            }
            if(commande[i]=='+' || commande[i]=='-'){ /*si aucun attribut (ou aucun attribut valable) n'a ete trouve alors renvoyer un attribut vide*/
                return ' ';
            }
        } else {
            if(commande[i]==','){ /*si on rencontre la premiere virgule la variable commencer devient 1*/
                commencer++;
            }
        }
    }
    return ' ';
}

int extraire_equipement_valeur(char *commande){
    /*renvoie la valeur de l'attribut de l'equipement a partir de la commande*/
    int valeur = 0;
    int dec = 1;
    int i;
    int commencer = 0; /*pour savoir quand commencer*/
    int signe = 0; /*pour savoir le signe : 1 si positif, -1 si negatif*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 1){ /*on commence apres avoir rencontre la premiere virgule*/
            if(commande[i]==','){ /*lorsqu'on rencontre la seconde virgule, on retourne la valeur de l'attribut*/
                valeur = valeur * signe;
                return valeur;
            }
            if(commande[i]>='0' && commande[i]<='9'){
                valeur = valeur*dec+(commande[i]-'0');
                dec = 10;
            } else if(commande[i]=='+'){ /*signe est 1 si positif, -1 si negatif*/
                signe = 1;
            } else if(commande[i]=='-'){
                signe = -1;
            }
        } else {
            if(commande[i]==','){ /*si on rencontre la premiere virgule la variable commencer devient 1*/
                commencer++;
            }
        }
    }
    return -1;
}

int equipement_len_classe(char *commande){
    /*renvoie le nombre de caracteres du nom de la classe de l'equipement*/
    int i;
    int n = 0;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 2){ /*on commence apres avoir rencontre la deuxieme virgule*/
            if(commande[i]=='}'){ /*lorsqu'on arrive a la fin, on retourne la valeur de n*/
                return n;
            } else if(commande[i]!=' '){
                n++;
            }
        } else {
            if(commande[i]==','){ /*pour chaque virgule qu'on rencontre on augmente commencer de 1*/
                commencer++;
            }
        }
    }
    return -1;
}

int extraire_equipement_classe(char *commande){
    /*renvoie la classe de l'equipement*/
    int len_classe = equipement_len_classe(commande);
    char *nom = stdprof_malloc((len_classe+1)*sizeof(char));
    int i;
    int j = 0;
    int commencer = 0; /*pour savoir quand commencer*/
    for(i=0;i<strlen(commande);i++){
        if(commencer == 2){ /*on commence apres avoir rencontre la deuxieme virgule*/
            if(commande[i]=='}'){ /*lorsqu'on arrive a la fin, on retourne la classe*/
                nom[j]='\0';
                if(strcmp(nom,"chaussures")==0){
                    stdprof_free(nom);
                    return 0;
                } else if(strcmp(nom,"protections")==0){
                    stdprof_free(nom);
                    return 1;
                } else if(strcmp(nom,"armes")==0){
                    stdprof_free(nom);
                    return 2;
                }
            } else if(commande[i]!=' '){ 
                nom[j]=commande[i];
                j++;
            }  
        } else {
            if(commande[i]==','){ /*pour chaque virgule qu'on rencontre on augmente commencer de 1*/
                commencer++;
            }
        }
    }
    stdprof_free(nom);
    return -1; /*lorsque la classe de l'equipement et ni chaussures ni protections ni armes alors on renvoie -1*/
}

equipement creation_equipement(char *commande){
    /*fonction qui cree l'equipement*/
    equipement Eq;
    Eq.nom = extraire_equipement_nom(commande);
    Eq.attribut = extraire_equipement_attribut(commande);
    Eq.valeur = extraire_equipement_valeur(commande);
    Eq.classe = extraire_equipement_classe(commande);
    Eq.x = -1;
    Eq.y = -1;
    return Eq;
}

void liberer_equipement(equipement Eq){
    /*libere la memoire occupe par le nom de l'equipement*/
    stdprof_free(Eq.nom);
}

ensemble_equipement creation_ensemble_equipement(){
    /*cree l'ensemble de equipement ou seront stocker tout les equipements du jeu*/
    ensemble_equipement E;
    int taille = 1;
    E.memoire = stdprof_malloc(taille*sizeof(equipement));
    E.taille = taille;
    E.n = 0;
    return E;
}

void liberer_ensemble_equipement(ensemble_equipement *E){
    /*libere l'ensemble de equipement ou sont stocker tout les equipements du jeu*/
    int i;
    for(i=0;i<E->n;i++){
        liberer_equipement(E->memoire[i]);
    }
    stdprof_free(E->memoire);
}

void liberer_ensemble_equipement_rahan(ensemble_equipement *E){
    /*libere les equipements de rahan*/
    int i;
    for(i=0;i<E->n;i++){
        if(strncmp(E->memoire[i].nom,"VIDE\0",5)==0){
            liberer_equipement(E->memoire[i]);
        }
    }
    stdprof_free(E->memoire);
}

void placer_equipement(equipement *Eq, grid G, int x, int y){
    /*place un equipement sur la grille du jeu en (x,y)*/
    Eq->x = x;
    Eq->y = y;
    G[y+2][(x+1)*2]='!';
    printf("[!] Placement effectué de :\n");
    afficher_equipement(Eq);
    printf("Coordonnees : (%d,%d)\n\n",x,y);
}

void agrandir_ensemble_equipement(ensemble_equipement *E){
    /*si l'ensemble n'est pas assez grand, on l'agrandit pour pouvoir stocker plus d'equipements*/
    int i;
    equipement *ancienne_mem = E->memoire;
    equipement *nouv_mem = stdprof_malloc((E->taille)*2 * sizeof(equipement));
    for(i=0;i<(E->n);i++){ /*apres avoir supprimer l'equipement on avance tout les equipements stocke apres dans l'ensemble pour ne pas de laisser de trou dans l'ensemble de equipement*/
        nouv_mem[i]=ancienne_mem[i];
    }
    stdprof_free(E->memoire);
    E->memoire = nouv_mem;
    E->taille = (E->taille)*2;
}

void ajouter_equipement(ensemble_equipement *E, char *commande){
    /*ajoute un equipement au jeu, apres de le creer*/
    if(E->n == E->taille){
        agrandir_ensemble_equipement(E);
    }
    E->memoire[E->n] = creation_equipement(commande);
    (E->n)++;
}

int identifier_equipement(ensemble_equipement *E, grid G, int x, int y){
    /*identifie quel equipement se situe aux coordonnees (x,y)*/
    int i;
    for(i=0;i<E->n;i++){
        if(E->memoire[i].x == x && E->memoire[i].y == y){
            return i;
        }
    }
    return -1;
}

void supprimer_equipement(int id, ensemble_equipement *E, grid G){
    /*supprime un equipement du jeu*/
    int i;
    enlever(G,E->memoire[id].x,E->memoire[id].y);
    liberer_equipement(E->memoire[id]);
    for(i=id;i<(E->n)-1;i++){
        E->memoire[i]=E->memoire[i+1];
    }
    E->n = E->n - 1;
}

char * equipement_nom_vide(void){
    /*retourne le nom VIDE pour un equipement vide*/
    char *nom = stdprof_malloc(10*sizeof(char));
    nom[0]='V';
    nom[1]='I';
    nom[2]='D';
    nom[3]='E';
    nom[4]='\0';
    return nom;
}

equipement creation_equipement_vide(int c){
    /*retourne un equipement vide*/
    equipement E;
    E.nom = equipement_nom_vide();
    E.attribut = ' ';
    E.valeur = 0;
    E.classe = c;
    E.x = -1;
    E.y = -1;
    return E;
}

void initialiser_equipement_rahan_vide(ensemble_equipement *E){
    /*initialise l'equipement de rahan a vide, represente par des equipements vides (c'est a dire des equipements de nom VIDE sans bonus pour rahan)*/
    int i;
    for(i=0;i<3;i++){
        if(E->n == E->taille){
            agrandir_ensemble_equipement(E);
        }
        E->memoire[E->n] = creation_equipement_vide(i);
        (E->n)++;
    }
}

void afficher_equipement(equipement *Eq){
    /*affiche les stats de l'equipement*/
    printf("[Equipement]\nNom : %s\n",Eq->nom);
    printf("Attribut : %c\n",Eq->attribut);
    printf("Valeur : %d\n",Eq->valeur);
    if(Eq->classe == chaussures){
        printf("Classe : chaussures\n");
    } else if(Eq->classe == protections){
        printf("Classe : protections\n");
    } else if(Eq->classe == armes){
        printf("Classe : armes\n");
    }
}

void afficher_equipements_rahan(equipement *Eq){
    /*affiche les stats de l'equipement et affiche VIDE si un equipement vide en argument*/
    if(strncmp(Eq->nom,"VIDE\0",5)==0){
        printf("VIDE\n");
    } else {
        printf("Nom : %s\n",Eq->nom);
        printf("Attribut : %c\n",Eq->attribut);
        printf("Valeur : %d\n",Eq->valeur);
    }
}

void afficher_tout_equipements_rahan(ensemble_equipement *E){
    /*affiche tout les equipements de rahan*/
    printf("[!] Affichage de l'équipement du héros :\n");
    printf("[Equipement] chaussures :\n");
    afficher_equipements_rahan(&(E->memoire)[0]);
    printf("[Equipement] protections :\n");
    afficher_equipements_rahan(&(E->memoire)[1]);
    printf("[Equipement] armes :\n");
    afficher_equipements_rahan(&(E->memoire)[2]);
    printf("[!] ___________________________________ \n\n");
}

void procede_equipement(grid G, int *x, int *y, ensemble_equipement *E, char *commande){
    /*fonction qui s'occupe du placement de l'equipement*/
    if(place_sur_grille(G,*x,*y)){ /*Si il y a de la place en (x,y) alors*/
        ajouter_equipement(E,commande); /*on stocke l'equipement dans la memoire*/
        if(E->memoire[(E->n)-1].classe>2 || E->memoire[(E->n)-1].classe<0){ /*Si l'equipement n'a pas de classe valide alors on affiche ce Warning, et on supprime cet equipement qui vient d'etre stocke dans la memoire*/
            fprintf(stderr,"[WARNING] Les équipements doivent seulement être de classe : chaussures, protections, ou armes.\n\n");
            supprimer_equipement((E->n)-1,E,G);
        } else { /*Sinon*/
            placer_equipement(&(E->memoire[(E->n)-1]),G,*x,*y); /*on place l'equipement en (x,y)*/
        }
    } else if (coords_invalides(*x,*y)){ /*Sinon si ce n'est pas possible parceque les coordonnees sont erronees Alors envoyer le Warning suivant, et ne pas stocker l'equipement dans la memoire (et ne pas le placer sur la grille)*/
        fprintf(stderr,"[WARNING] Attention les coordonnées sont erronées. Il doivent être dans la limite du plan de jeu.\n\n");
    } else { /*Sinon envoyer le Warning suivant, et ne pas stocker l'equipement dans la memoire (et ne pas le placer sur la grille)*/
        fprintf(stderr,"[WARNING] Impossible de placer le equipement. Autre chose est déjà présente aux coordonnées (%d,%d).\n\n",*x,*y);
    }
    *x = -1; /*On a plus besoins des coordonnees*/
    *y = -1; /*On les mets donc a -1*/
}
