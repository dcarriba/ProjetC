#include <stdio.h>
#include <stdlib.h>
#include "stdprof.h"
#include "personnages.h"
#include "monstres.h"
#include "nourritures.h"
#include "equipements.h"
#include "grid.h"

hero creation_rahan(void){
    /*creation de Rahan*/
    hero rahan;
    rahan.nom = "Rahan";
    rahan.pts_vie = 50;
    rahan.sante = 50;
    rahan.force = 10;
    rahan.vitesse = 1;
    return rahan;
}

demiurge creation_olivier(void){
    /*creation de Olivier*/
    demiurge olivier;
    olivier.nom = 'Y';
    return olivier;
}


void placer_demiurge(demiurge *D, grid G, int x, int y){
    /*place (si possible) le demiurge au coordonnees (x,y)*/
    if(placement_possible(G,x,y)){
        D->x = x;
        D->y = y;
        G[y+2][(x+1)*2]=D->nom;
    }
}

void placer_hero(hero *H, grid G, int x, int y){
    /*place (si possible) le heros au coordonnees (x,y)*/
    if(placement_possible(G,x,y)){
        H->x = x;
        H->y = y;
        G[y+2][(x+1)*2]=H->nom[0];
    }
}

void combat_hero_monstre(hero *H, int id, ensemble_monstre *EnsM, grid G){
    /*fonction qui gere le combat entre le heros et un monstre*/
    int tour = 1;
    printf("[-- COMBAT --]\n");
    printf("%s (Vie : %d/%d) VS %s (Vie : %d)\n",H->nom,H->sante,H->pts_vie,EnsM->memoire[id].nom,EnsM->memoire[id].vie);
    printf("[Debut]\n");
    while((H->sante)>0 && EnsM->memoire[id].vie >0){ /*le combat dure tant que le heros et le monstre sont en vie*/
        switch (tour%2)
        {
        case 1: /*c'est le tour du heros*/
            printf("Tour %d : %s attaque!\n",tour,H->nom);
            (EnsM->memoire[id].vie) = (EnsM->memoire[id].vie) - (H->force); /*le heros attaque*/
            tour++;
            if((H->sante)<0){ /*la vie ne peut pas etre inferieur a 0*/
                H->sante = 0;
            }
            printf("[Hero] %s : Vie : %d/%d\n",H->nom,H->sante,H->pts_vie);
            if(EnsM->memoire[id].vie <0){ /*la vie ne peut pas etre inferieur a 0*/
                EnsM->memoire[id].vie = 0;
            }
            printf("[Monstre] %s : Vie : %d (-%d)\n",EnsM->memoire[id].nom,EnsM->memoire[id].vie,H->force);
            break;
        case 0: /*c'est le tour du monstre*/
            printf("Tour %d : %s attaque!\n",tour,EnsM->memoire[id].nom);
            (H->sante)=(H->sante)-(EnsM->memoire[id].force); /*le monstre attaque*/
            tour++;
            if((H->sante)<0){ /*la vie ne peut pas etre inferieur a 0*/
                H->sante = 0;
            }
            printf("[Hero] %s : Vie : %d/%d (-%d)\n",H->nom,H->sante,H->pts_vie,EnsM->memoire[id].force);
            if(EnsM->memoire[id].vie <0){ /*la vie ne peut pas etre inferieur a 0*/
                EnsM->memoire[id].vie = 0;
            }
            printf("[Monstre] %s : Vie : %d\n",EnsM->memoire[id].nom,EnsM->memoire[id].vie);
            break;
        default:
            break;
        }
    }
    printf("[Fin]\n");
    if((H->sante)>0 && EnsM->memoire[id].vie <=0){ /*le heros a gagne le combat*/
        printf("Vainqueur : %s!\n",H->nom);
    } else if((H->sante)<=0){ /*le monstre a gagne le combat*/
        printf("Vainqueur : %s!\n",EnsM->memoire[id].nom);
    }
    printf("A la fin : ");
    printf("%s : Vie : %d/%d ; ",H->nom,H->sante,H->pts_vie);
    printf("%s : Vie : %d\n",EnsM->memoire[id].nom,EnsM->memoire[id].vie); /*on affiche les stats du heros et du monstre a la fin*/
    printf("[-- FIN DU COMBAT --]\n\n");
}

void manger_hero_nourriture(hero *H, int id, ensemble_nourriture *EnsN, grid G){
    /*fonction qui gere le heros qui mange*/
    if((H->sante + EnsN->memoire[id].valeur)>=H->pts_vie){ /*le heros ne peut pas regenerer plus de vie qu'il n'a de points de vie*/
        H->sante = H->pts_vie; /*il regenere donc au maximum*/
        printf("[Nourriture] %s mange : %s (%s), et regagne son maximum de Santé.\n\n",H->nom,EnsN->memoire[id].nom,EnsN->memoire[id].description);
    } else {
        H->sante = H->sante + EnsN->memoire[id].valeur; /*le heros regenere un certain nombre de sante*/
        printf("[Nourriture] %s mange : %s (%s), et regagne : %d de Santé.\n\n",H->nom,EnsN->memoire[id].nom,EnsN->memoire[id].description,EnsN->memoire[id].valeur);
    }
    supprimer_nourriture(id,EnsN,G); /*le heros a mange la nourriture, on peut donc la supprimer du jeu et de la memoire*/
}

void equipper_hero_equipement(hero *H, int id, ensemble_equipement *EnsE, grid G, ensemble_equipement *EnsE_rahan){
    /*fonction qui gere l'equipement d'equipement (avec pas plus d'un equipement equipé par classe)*/
    if(EnsE->memoire[id].valeur>EnsE_rahan->memoire[EnsE->memoire[id].classe].valeur){ /*Si l'equipement donne de meilleurs stats que celui qu'il a deja, ou si il en a pas encore (de la meme classe)*/
        if(EnsE_rahan->memoire[EnsE->memoire[id].classe].valeur!=0){ /*Il a deja un equipement donc*/
            switch (EnsE_rahan->memoire[EnsE->memoire[id].classe].attribut) /*il faut enlever les stats que celui lui donnait*/
            {
            case 'F':
                H->force = H->force - EnsE_rahan->memoire[EnsE->memoire[id].classe].valeur;
                break;
            case 'P':
                H->pts_vie = H->pts_vie - EnsE_rahan->memoire[EnsE->memoire[id].classe].valeur;
                break;
            case 'V':
                H->vitesse = H->vitesse - EnsE_rahan->memoire[EnsE->memoire[id].classe].valeur;
                break;
            default:
                break;
            }
            printf("[Equipement] %s enlève l'équipement: %s.\n",H->nom,EnsE_rahan->memoire[EnsE->memoire[id].classe].nom);
        } else { /*il n'avait pas deja d'equipement, il faut donc enlever l'equipement VIDE qui était juste placeholder*/
            liberer_equipement(EnsE_rahan->memoire[EnsE->memoire[id].classe]);
        }
        EnsE->memoire[id].x = -1;
        EnsE->memoire[id].y = -1;
        switch (EnsE->memoire[id].attribut) /*on equipe le nouvel equipement*/
        {
        case 'F':
            H->force = H->force + EnsE->memoire[id].valeur;
            printf("[Equipement] %s équippe : %s, et gagne : %d de Force.\n\n",H->nom,EnsE->memoire[id].nom,EnsE->memoire[id].valeur);
            EnsE_rahan->memoire[EnsE->memoire[id].classe]=EnsE->memoire[id];
            break;
        case 'P':
            H->pts_vie = H->pts_vie + EnsE->memoire[id].valeur;
            printf("[Equipement] %s équippe : %s, et gagne : %d de Points de Vie.\n\n",H->nom,EnsE->memoire[id].nom,EnsE->memoire[id].valeur);
            EnsE_rahan->memoire[EnsE->memoire[id].classe]=EnsE->memoire[id];
            break;
        case 'V':
            H->vitesse = H->vitesse + EnsE->memoire[id].valeur;
            printf("[Equipement] %s équippe : %s, et gagne : %d de Vitesse.\n\n",H->nom,EnsE->memoire[id].nom,EnsE->memoire[id].valeur);
            EnsE_rahan->memoire[EnsE->memoire[id].classe]=EnsE->memoire[id];
            break;
        default:
            break;
        }
    } else { /*L'equipement ne donne pas de meilleurs stats que celui qu'il a deja, donc on ne l'equipe pas et on le supprime du jeu et de la memoire*/
        supprimer_equipement(id,EnsE,G);
    }
}

void bouger(hero *H, int X, int Y, grid G, ensemble_monstre *EnsM, ensemble_nourriture *EnsN, ensemble_equipement *EnsE, ensemble_equipement *EnsE_rahan){
    /*fonction qui deplace le heros dans la direction voulue (si le placement est bien possible)*/
    int V = (H->vitesse);
    int i,id;
    for(i=0;i<V;i++){ /*prend en compte la vitesse du heros*/
        if(placement_possible(G,(H->x)+X,(H->y)+Y) && monstre_sur_grille(G,(H->x)+X,(H->y)+Y)){ /*si le heros rencontre un monstre*/
            id = identifier_monstre(EnsM,G,(H->x)+X,(H->y)+Y); /*on identifie le monstre qu'il vient de rencontrer*/
            combat_hero_monstre(H,id,EnsM,G); /*le combat se lance*/
            if((H->sante)>0 && EnsM->memoire[id].vie <=0){ /*le heros a gagne le combat*/
                supprimer_monstre(id,EnsM,G); /*on supprime le monstre du jeu et de la memoire*/
                enlever(G,(H->x),(H->y));
                placer_hero(H,G,(H->x)+X,(H->y)+Y); /*on place le leros a sa nouvelle position*/
            } else if((H->sante)<=0){ /*le heros a perdu le combat*/
                enlever(G,(H->x),(H->y));
            }
            i=H->vitesse; /*apres un combat le heros s'arrete*/
        } else if(placement_possible(G,(H->x)+X,(H->y)+Y) && nourriture_sur_grille(G,(H->x)+X,(H->y)+Y)){ /*si le heros rencontre de la nourriture*/
            id = identifier_nourriture(EnsN,G,(H->x)+X,(H->y)+Y);
            manger_hero_nourriture(H,id,EnsN,G); /*le heros mange*/
            enlever(G,(H->x),(H->y));
            placer_hero(H,G,(H->x)+X,(H->y)+Y);
        } else if(placement_possible(G,(H->x)+X,(H->y)+Y) && equipement_sur_grille(G,(H->x)+X,(H->y)+Y)){ /*si le heros rencontre de l'equipement*/
            id = identifier_equipement(EnsE,G,(H->x)+X,(H->y)+Y);
            equipper_hero_equipement(H,id,EnsE,G,EnsE_rahan); /*le heros equipe l'equipement*/
            enlever(G,(H->x),(H->y));
            placer_hero(H,G,(H->x)+X,(H->y)+Y);
        } else if(placement_possible(G,(H->x)+X,(H->y)+Y)){ /*si le heros ne rencontre rien*/
            enlever(G,(H->x),(H->y));
            placer_hero(H,G,(H->x)+X,(H->y)+Y); /*on le deplace*/
        }
    }
}

void deplacement(hero *H, char C, grid G, ensemble_monstre *EnsM, ensemble_nourriture *EnsN, ensemble_equipement *EnsE, ensemble_equipement *EnsE_rahan){
    /*fonction qui deplace le heros en fonction de l'entree de d'utilisateur*/
    switch (C)
    {
    case 'H':
        bouger(H,0,-1,G,EnsM,EnsN,EnsE,EnsE_rahan); /*on deplace vers le haut*/
        break;
    case 'G':
        bouger(H,-1,0,G,EnsM,EnsN,EnsE,EnsE_rahan); /*on deplace vers la gauche*/
        break;
    case 'D':
        bouger(H,1,0,G,EnsM,EnsN,EnsE,EnsE_rahan); /*on deplace vers la droite*/
        break;
    case 'B':
        bouger(H,0,1,G,EnsM,EnsN,EnsE,EnsE_rahan); /*on deplace vers le bas*/
        break;
    default:
        break;
    }
}

/*fonctions IA :*/
int ia_trouve_bonus_haut(grid G, int x, int y){
    /*renvoie True si il y a un bonus en haut*/
    return (nourriture_sur_grille(G,x,y-1) || equipement_sur_grille(G,x,y-1)); 
}

int ia_trouve_bonus_droite(grid G, int x, int y){
    /*renvoie True si il y a un bonus a droite*/
    return (nourriture_sur_grille(G,x+1,y) || equipement_sur_grille(G,x+1,y)); 
}

int ia_trouve_bonus_bas(grid G, int x, int y){
    /*renvoie True si il y a un bonus en bas*/
    return (nourriture_sur_grille(G,x,y+1) || equipement_sur_grille(G,x,y+1)); 
}

int ia_trouve_bonus_gauche(grid G, int x, int y){
    /*renvoie True si il y a un bonus a gauche*/
    return (nourriture_sur_grille(G,x-1,y) || equipement_sur_grille(G,x-1,y)); 
}

int ia_trouve_malus_haut(grid G, int x, int y){
    /*renvoie True si il y a un malus en haut*/
    return (monstre_sur_grille(G,x,y-1) || rocher_sur_grille(G,x,y-1)); 
}

int ia_trouve_malus_droite(grid G, int x, int y){
    /*renvoie True si il y a un malus a droite*/
    return (monstre_sur_grille(G,x+1,y) || rocher_sur_grille(G,x+1,y)); 
}

int ia_trouve_malus_bas(grid G, int x, int y){
    /*renvoie True si il y a un malus en bas*/
    return (monstre_sur_grille(G,x,y+1) || rocher_sur_grille(G,x,y+1)); 
}

int ia_trouve_malus_gauche(grid G, int x, int y){
    /*renvoie True si il y a un malus a gauche*/
    return (monstre_sur_grille(G,x-1,y) || rocher_sur_grille(G,x-1,y)); 
}

void ivoire_albe(hero *H, grid G, ensemble_monstre *EnsM, ensemble_nourriture *EnsN, ensemble_equipement *EnsE, ensemble_equipement *EnsE_rahan){
    /*fonction IA principale*/
    int x = H->x;
    int y = H->y;
    int V = H->vitesse;
    char direction = ' ';
    /*l'IA fait sa decision en regardant autour du heros (plus d'explications de l'IA sont a la fin du fichier LISEZMOI.txt)*/
    if(ia_trouve_bonus_haut(G,x,y)){
        direction = 'H';
    } else if(ia_trouve_bonus_droite(G,x,y)){
        direction = 'D';
    } else if(ia_trouve_bonus_bas(G,x,y)){
        direction = 'B';
    } else if(ia_trouve_bonus_gauche(G,x,y)){
        direction = 'G';
    } else if(ia_trouve_malus_haut(G,x,y)){
        direction = 'B';
    } else if(ia_trouve_malus_droite(G,x,y)){
        direction = 'G';
    } else if(ia_trouve_malus_bas(G,x,y)){
        direction = 'H';
    } else if(ia_trouve_malus_gauche(G,x,y)){
        direction = 'D';
    }
    if(direction==' '){ /*par defaut l'IA deplace le heros vers le haut*/
        direction = 'H';
    }
    printf("[!] Appel à l'Ivoire Albe. L'IA decide que rahan se déplace vers ");
    switch (direction)
    {
    case 'H':
        printf("le haut.\n\n");
        break;
    case 'D':
        printf("la droite.\n\n");
        break;
    case 'B':
        printf("le bas.\n\n");
        break;
    case 'G':
        printf("la gauche.\n\n");
        break;
    
    default:
        break;
    }
    H->vitesse = 1; /*l'IA fait deplacer le heros de seulement une case*/
    deplacement(H,direction,G,EnsM,EnsN,EnsE,EnsE_rahan);
    H->vitesse = V;
}
/*fin des fonctions IA*/

void afficher_stats(hero *H){
    /*affiche les stats du hero*/
    printf("[!] Invocation des Stats :\n");
    printf("[Hero]\nNom : %s\n",H->nom);
    printf("Coordonnees : (%d,%d)\n",H->x,H->y);
    printf("Points de vie : %d\n",H->pts_vie);
    printf("Sante : %d\n",H->sante);
    printf("Force : %d\n",H->force);
    printf("Vitesse : %d\n\n",H->vitesse);
}
