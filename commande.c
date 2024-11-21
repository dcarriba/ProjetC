#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdprof.h"
#include "personnages.h"
#include "grid.h"
#include "commande.h"

int commande_debut_erronee(char *commande){
    /*renvoie True si la commande est different de AUBE ou A*/
    return (strncmp(commande,"AUBE ",5) != 0    && 
            strncmp(commande,"AUBE\n",5) != 0   &&
            strncmp(commande,"A\n",2) != 0      );
}

int commande_de_mouvement(char *commande){
    /*renvoie True si c'est une commande de mouvement*/
    return (strncmp(commande,"HAUT ",5) == 0    ||
            strncmp(commande,"HAUT\n",5) == 0   ||
            strncmp(commande,"H\n",2) == 0      ||
            strncmp(commande,"GAUCHE ",7) == 0  ||
            strncmp(commande,"GAUCHE\n",7) == 0 ||
            strncmp(commande,"G\n",2) == 0      ||
            strncmp(commande,"DROITE ",7) == 0  ||
            strncmp(commande,"DROITE\n",7) == 0 ||
            strncmp(commande,"D\n",2) == 0      ||
            strncmp(commande,"BAS ",4) == 0     ||
            strncmp(commande,"BAS\n",4) == 0    ||
            strncmp(commande,"B\n",2) == 0      );
}

int commande_de_vision(char *commande){
    /*renvoie True si c'est la commmande VISION ou V*/
    return (strncmp(commande,"VISION ",7) == 0  ||
            strncmp(commande,"VISION\n",7) == 0 ||
            strncmp(commande,"V\n",2) == 0      );
}

int commande_invocation(char *commande){
    /*renvoie True si c'est la commmande INVOCATION ou I*/
    return (strncmp(commande,"INVOCATION ",11) == 0     ||
            strncmp(commande,"INVOCATION\n",11) == 0    ||
            strncmp(commande,"I\n",2) == 0              );
}

int commande_rocher(char *commande){
    /*renvoie True si c'est la commmande ROCHER ou R*/
    return (strncmp(commande,"ROCHER ",7) == 0  ||
            strncmp(commande,"ROCHER\n",7) == 0 ||
            strncmp(commande,"R\n",2) == 0 );
}

int commande_coord_abs(char *commande){
    /*renvoie True si c'est une commande de coordonnee absolue*/
    return (strncmp(commande,"X=",2) == 0       ||
            strncmp(commande,"Y=",2) == 0       );
}

int commande_coord_rel_demiurge(char *commande){
    /*renvoie True si c'est une commande de coordonnee relative au demiurge Olivier*/
    return (strncmp(commande,"dx=",3) == 0      ||
            strncmp(commande,"dy=",3) == 0      );
}

int commande_coord_rel_hero(char *commande){
    /*renvoie True si c'est une commande de coordonnee relative au heros Rahan*/
    return (strncmp(commande,"DX=",3) == 0      ||
            strncmp(commande,"DY=",3) == 0      );
}

int recuperer_coord(int i, char *commande){
    /*recupere les coordonnees donnees par l'utilisateur*/
    int z = 0;
    int dec = 1;
    while(commande[i]>='0' && commande[i]<='9'){
        z=z*dec+(commande[i]-'0');
        i++;
        dec = 10;
    }
    return z;
}

void save_coord_abs(char *commande, int *x, int *y){
    /*sauvegarde les coordonnees absolues, donnees par l'utilisateur*/
    if(commande[0]=='X'){
        *x = recuperer_coord(2,commande);
    } else if (commande[0]=='Y'){
        *y = recuperer_coord(2,commande);
    }
}

void save_coord_rel_demiurge(char *commande, int *x, int *y, demiurge *D){
    /*sauvegarde les coordonnees relatives au demiurge, donnees par l'utilisateur*/
    if(commande[1]=='x'){
        if(commande[3]=='+'){
            *x = (D->x)+recuperer_coord(4,commande);
        } else if(commande[3]=='-'){
            *x = (D->x)-recuperer_coord(4,commande);
        }
    } else if (commande[1]=='y'){
        if(commande[3]=='+'){
            *y = (D->y)+recuperer_coord(4,commande);
        } else if(commande[3]=='-'){
            *y = (D->y)-recuperer_coord(4,commande);
        }
    }
}

void save_coord_rel_hero(char *commande, int *x, int *y, hero *H){
    /*sauvegarde les coordonnees relatives au heros, donnees par l'utilisateur*/
    if(commande[1]=='X'){
        if(commande[3]=='+'){
            *x=(H->x)+recuperer_coord(4,commande);
        } else if(commande[3]=='-'){
            *x=(H->x)-recuperer_coord(4,commande);
        }
    } else if (commande[1]=='Y'){
        if(commande[3]=='+'){
            *y=(H->y)+recuperer_coord(4,commande);
        } else if(commande[3]=='-'){
            *y=(H->y)-recuperer_coord(4,commande);
        }
    }
}

int commande_monstre(char *commande){
    /*renvoie True si c'est une commande de monstre*/
    return (strncmp(commande,"<",1) == 0 );
}

int commande_equipement(char *commande){
    /*renvoie True si c'est une commande de equipement*/
    return (strncmp(commande,"{",1) == 0 );
}

int commande_nourriture(char *commande){
    /*renvoie True si c'est une commande de nourriture*/
    return (strncmp(commande,"(",1) == 0 );
}

int commande_trier(char *commande){
    /*renvoie True si c'est la commmande TRIER*/
    return (strncmp(commande,"TRIER ",6) == 0   ||
            strncmp(commande,"TRIER\n",6) == 0  );
}

int commande_ia(char *commande){
    /*renvoie True si c'est la commmande IA*/
    return (strncmp(commande,"IA ",3) == 0      ||
            strncmp(commande,"IA\n",3) == 0     );
}

int commande_de_fin(char *commande){
    /*renvoie True si c'est la commmande CREPUSCULE ou C*/
    return (strncmp(commande,"CREPUSCULE\0",11) == 0    ||
            strncmp(commande,"CREPUSCULE ",11) == 0     ||
            strncmp(commande,"CREPUSCULE\n",11) == 0    ||
            strncmp(commande,"C\0",2) == 0              ||
            strncmp(commande,"C ",2) == 0               ||
            strncmp(commande,"C\n",2) == 0              );
}
