#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdprof.h"
#include "personnages.h"
#include "grid.h"
#include "commande.h"
#include "monstres.h"
#include "nourritures.h"
#include "equipements.h"

void jeu(FILE *fichier){
    int x = -1; /*on stockera les coordonnees donnee par l'utilisateur ici*/
    int y = -1;
    int test_aube = 1; /*variable pour savoir si on est a la premiere ligne pour tester que le fichier commence bien par AUBE (ou A au format simple)*/
    int crepuscule = 0; /*variable pour savoir si le fichier fini bien par CREPUSULE (ou C au format simple)*/
    int taille_commande = 256; /*on suppose que chaque ligne dans le fichier (ou entree standard) ne depasse pas 256 caracteres (suffisant pour tout les commandes de mouvements, etc.) Vous pouvez la changer*/
    char *commande = stdprof_malloc(taille_commande*sizeof(char)); /*on cree le tampon pour stocker chaque ligne du fichier (ou entree standard)*/
    ensemble_monstre ens_monstre = creation_ensemble_monstre(); /*on cree un ensemble de monstre ou on stockera tout les monstres ajoutes par l'utilisateur*/
    ensemble_nourriture ens_nourriture = creation_ensemble_nourriture(); /*on cree un ensemble de nourriture ou on stockera toutes les nourritures ajoutes par l'utilisateur*/
    ensemble_equipement ens_equipement = creation_ensemble_equipement(); /*on cree un ensemble de equipements ou on stockera tout les equipements ajoutes par l'utilisateur*/
    ensemble_equipement ens_equipement_rahan = creation_ensemble_equipement(); /*on cree un ensemble de equipements propre a Rahan ou on stockera tout les equipements que Rahan equipe*/
    grid grille = initialisation(); /*on initialise la grille du jeu*/
    hero rahan = creation_rahan();
    demiurge olivier = creation_olivier();
    initialiser_equipement_rahan_vide(&ens_equipement_rahan); /*Rahan commence sans equipements*/
    placer_demiurge(&olivier,grille,5,5);
    placer_hero(&rahan,grille,5,4);
    while(fgets(commande, taille_commande, fichier) != NULL){ /*boucle principale*/
        if(test_aube==1){ /*si on est a la premiere ligne il faut tester que celle-ci est bien AUBE (ou A si au format simple)*/
            if(commande_debut_erronee(commande)){
                fprintf(stderr,"[ERREUR] Fichier ou Entree invalide! Il/Elle doit commencer par AUBE (ou A si format simple).\n");
                liberer_ensemble_monstre(&ens_monstre); /*on libere la memoire*/
                liberer_ensemble_nourriture(&ens_nourriture);
                liberer_ensemble_equipement_rahan(&ens_equipement_rahan);
                liberer_ensemble_equipement(&ens_equipement);
                stdprof_free(commande);
                liberer_grid(grille);
                fclose(fichier); /*on ferme le fichier*/
                stdprof_afficher();
                exit(3);
            }
            test_aube=0; /*on vient des tester si le fichier commence par AUBE (ou A au format simple), pas besoin de retester, donc on met test_aube a 0*/
        } else if(commande_de_mouvement(commande)){
            deplacement(&rahan,commande[0],grille,&ens_monstre,&ens_nourriture,&ens_equipement,&ens_equipement_rahan);
        } else if(commande_de_vision(commande)){
            affichage(grille);
            printf("\n");
        } else if (commande_coord_abs(commande)){
            save_coord_abs(commande,&x,&y);
        } else if (commande_coord_rel_demiurge(commande)){
            save_coord_rel_demiurge(commande,&x,&y,&olivier);
        } else if (commande_coord_rel_hero(commande)){
            save_coord_rel_hero(commande,&x,&y,&rahan);
        } else if(commande_rocher(commande)){
            procede_rocher(grille,&x,&y); /*Place le rocher sur la grille*/
        } else if(commande_invocation(commande)){
            afficher_stats(&rahan);
        } else if(commande_monstre(commande)){
            procede_monstre(grille,&x,&y,&ens_monstre,commande); /*Cree le monstre, le stocke dans la memoire et le place sur la grille*/
        } else if(commande_nourriture(commande)){
            procede_nourriture(grille,&x,&y,&ens_nourriture,commande); /*Cree la nourriture, la stocke dans la memoire et la place sur la grille*/
        } else if(commande_equipement(commande)){
            procede_equipement(grille,&x,&y,&ens_equipement,commande); /*Cree l'equipement, le stocke dans la memoire et le place sur la grille*/
        } else if(commande_trier(commande)){
            afficher_tout_equipements_rahan(&ens_equipement_rahan);
        } else if(commande_ia(commande)){
            ivoire_albe(&rahan,grille,&ens_monstre,&ens_nourriture,&ens_equipement,&ens_equipement_rahan);
        } else if(commande_de_fin(commande)){
            printf("[!] Fin du jeu suite à la commande CREPUSCULE.\n");
            crepuscule = 1;
            break;
        } else if(rahan.sante <= 0){ /*Si Rahan meurt*/
            printf("[!] Fin du jeu. Rahan est mort.\n");
            crepuscule = 1;
            break;
        }
    }
    liberer_ensemble_monstre(&ens_monstre); /*on libere la memoire*/
    liberer_ensemble_nourriture(&ens_nourriture);
    liberer_ensemble_equipement_rahan(&ens_equipement_rahan);
    liberer_ensemble_equipement(&ens_equipement);
    stdprof_free(commande);
    liberer_grid(grille);
    fclose(fichier); /*on ferme le fichier*/
    if(crepuscule==0){ /*Si le fichier ne finit pas par CREPUSCULE (ou C si format simple) alors on a une erreur*/
        fprintf(stderr,"[ERREUR] Fichier ou Entree invalide! Il/Elle doit finir par CREPUSCULE (ou C si format simple).\n");
        stdprof_afficher();
        exit(4);
    }
}

int main(int argc, char* argv[]){
    FILE * fichier;
    char * nom_fichier;
    if(argc==1){ /*Si on ne donne rien en argument*/
        jeu(stdin); /*Alors le jeu s'execute a partir de l'entree standard*/
    } else if(argc==2){ /*Si on donne 1 argument*/
        nom_fichier = argv[1];
        if ((fichier=fopen(nom_fichier,"r")) == NULL) { /*Si fichier existe pas Alors erreur*/
            fprintf(stderr,"[ERREUR] Erreur de lecture du ficher : %s\n",nom_fichier);
            stdprof_afficher();
            exit(1);
        }
        jeu(fichier); /*le jeu s'execute a partir d'un fichier*/
    } else { /*Si on donne plus de 1 arguments Alors il y a une erreur*/
        fprintf(stderr,"[ERREUR] Veuillez ne pas donner plus d'un fichier en argument.\n");
        stdprof_afficher();
        exit(2);
    }
    stdprof_afficher();
    return 0;
}
