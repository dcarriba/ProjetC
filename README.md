# ProjetC
Projet de Programmation C - L2 info S3

MEMBRE DU GROUPE : Daniel CARRIBA NOSRATI


CHOSES IMPLÉMENTÉES ET PAS IMPLÉMENTÉES :

Choses implémentées:
(Basique) :
- Affichage de la carte
- Déplacement de Rahan (avec une vitesse quelconque (de 1 à n))
- Jouer une partie à partir d’une description donnée sur la entree standard,
ainsi que jouer une partie à partir d'un ficher donné. (Les Formats Normal et Simple fonctionnent)
- Gestion des rochers
(Moyen) :
- Gestion des monstres et des combats
- Gestion de la nourriture
- Gestion des équipements (avec pas plus d'un équipement par classe d'équipement)
- Fin de la partie à la commande CREPUSCULE (ou C si Format Simple), ainsi que Fin de la partie lorsque Rahan meurt.
(Avancé) :
- une IA (description de son fonctionnement à la fin de ce ficher)

Choses Pas implémentées:
(Avancé) :
- La carte s’agrandit lorsque Rahan arrive au bord.
- Possibilité d’annuler les dernières commandes.
- Faire des sauvegardes/restaurations.


DANS LE ZIP :

- 8 fichiers .c et 7 fichiers .h :
	- programme.c (le fichier .c principal avec la fonction "main()")
	- grid.c
	- grid.h
	- commande.c
	- commande.h
	- personnages.c
	- personnages.h
	- monstres.c
	- monstres.h
	- nourritures.c
	- nourritures.h
	- equipements.c
	- equipements.h
	- stdprof.c
	- stdprof.h
- Le répertoire test/ avec 7 parties :
	- partie1.txt
	- partie2.txt
	- partie3.txt
	- partie4.txt
	- partie5.txt
	- partie6.txt
	- partie7.txt
- Le Makefile
- Ce document LISEZMOI.txt


DESCRIPTION :

I] Structures et Types définies:

1) le type "grid" (définie dans grid.h) :
Cet type renomme char** en grid.
Utile pour la grille du jeu, initialisée (dynamiquement avec des "stdprof_malloc()") comme un
tableau de tableaux de caractères.

2) la structure "hero" (définie dans personnages.h) :
Cette structure sert à stocker les informations de l'héros Rahan.

3) la structure "demiurge" (définie dans personnages.h) :
Cette structure sert à stocker les informations du démiurge Olivier (c'est à dire son nom 'Y' ainsi que ses coordonnées).

4) la structure "monstre" (définie dans monstres.h) :
Cette structure sert à stocker les informations des monstres.

5) la strcuture "ensemble_monstre" (définie dans monstres.h) :
Cette structure sert à stocker tout les monstres dans une mémoire allouée, ansi que de stocker les informations de
la taille de cette mémoire allouée et du nombre n de monstres effectivement stocké dans la mémoire.

6) la structure "nourriture" (définie dans nourritures.h) :
Cette structure sert à stocker les informations des nourritures.

7) la strcuture "ensemble_nourriture" (définie dans nourritures.h) :
Cette structure sert à stocker toutes les nourritures dans une mémoire allouée, ansi que de stocker les informations de
la taille de cette mémoire allouée et du nombre n de nourritures effectivement stocké dans la mémoire.

8) l'énumeration "classe_equipement" (définie dans equipements.h) :
Énumeration à 3 valeurs représentants les 3 classes d'équipements existantes, qui sont "chaussures", "protections" et "armes".

9) la structure "equipement" (définie dans equipements.h) :
Cette structure sert à stocker les informations des équipements.

10) la strcuture "ensemble_equipement" (définie dans equipements.h) :
Cette structure sert à stocker toutes les équipements dans une mémoire allouée, ansi que de stocker les informations de
la taille de cette mémoire allouée et du nombre n de équipements effectivement stocké dans la mémoire.

II] Description des fichiers .c :

1) programme.c :
C'est le fichier .c principal avec la fonction "main()".
Contient également la fonction "jeu()" qui s'occupe du jeu.

2) grid.c :
Ce fichier contient les fonctions utiles pour (et en rapport avec) la grille du jeu, comme notamment la fonction
"initialisation()" qui initialise au début la grille du jeu.
Ce fichier contient également les fonctions pour placer des rochers sur la grille.

3) commande.c :
Ce fichier contient les fonctions utiles pour reconnaitre les commandes données par l'utilisateur par entrée standard ou
fichier texte.

4) personnages.c :
Ce fichier contient les fonctions utiles pour (et en rapport avec) l'héros Rahan.
C'est à dire les fonctions pour la création de Rahan, son déplacement, la fonction pour
les combats entre Rahan et des monstres, la fonction pour que Rahan mange de la nourriture, 
la fonction pour que Rahan équipe de l'équipement, etc.
Ce fichier contient également la fonction pour l'IA.

5) monstres.c :
Ce fichier contient les fonctions utiles pour (et en rapport avec) les monstres.
C'est à dire les fonctions pour la création des monstres, les fonctions pour leurs stockage dans la mémoire, etc.

6) nourritures.c :
Ce fichier contient les fonctions utiles pour (et en rapport avec) les nourritures.
C'est à dire les fonctions pour la création des nourritures, les fonctions pour leurs stockage dans la mémoire, etc.

7) equipements.c :
Ce fichier contient les fonctions utiles pour (et en rapport avec) les équipements.
C'est à dire les fonctions pour la création des équipements, les fonctions pour leurs stockage dans la mémoire, etc.

8) stdprof.c :
Votre fichier avec vos fonctions :
"stdprof_malloc()", "stdprof_free()", etc.

III] Description des fichiers de test :

1) partie1.txt :
Une partie normale avec des monstres, de la nourriture, des equipements, des combats, etc.
La partie se finie de manière normale, grâce a la commande CREPUSCULE.

2) partie2.txt :
Une partie normale avec des monstres, de la nourriture, des equipements, des combats, etc.
Rahan meurt dans un combat et la partie se finie.

3) partie3.txt :
Une partie au format simple.
La partie se finie de manière normale, grâce a la commande C.

4) partie4.txt :
Une partie avec des monstres, de la nourriture, des equipements, des combats, etc.
Cette partie ne commence pas avec AUBE mais avec AUBEE.

5) partie5.txt :
Une partie avec des monstres, de la nourriture, des equipements, des combats, etc.
Cette partie ne finie pas avec CREPUSCULE mais avec CREPUSCUEE.

6) partie6.txt :
Une partie normale avec des monstres, de la nourriture, des equipements, des combats, etc.
Tout les équipements ont par contre des mauvaises classes (c'est à dire des classes non définies).
Pour le premier rocher, on oublie de renseigner des coordonnées.
La partie se finie de manière normale, grâce a la commande CREPUSCULE.

7) partie7.txt :
Une autre partie normale avec des monstres, de la nourriture, des equipements, des combats, etc.
La partie se finie de manière normale, grâce a la commande CREPUSCULE.


REMARQUES :

1) Classes des équipements :
- Les seules classes valables pour les équipements sont "chaussures", "protections" et "armes".
- Si une classe différente est renseigné le programme revoie comme warning :
"[WARNING] Les équipements doivent seulement être de classe : chaussures, protections, ou armes."
et ne place pas l'équipement sur la carte. Le jeu continue normalement.

2) Coordonnés pas renseignés ou invalides :
- Si l'utilisateur oublie de renseigner une (ou même les deux) coordonnées, ou si l'utilisateur renseigne pour coordonnée
un nombre trop grand ou trop petit (la grille du jeu est de taille 10*10, x et y doivent donc être compris entre 0
et 10), alors le programme renvoie comme warning :
"[WARNING] Attention les coordonnées sont erronées. Il doivent être dans la limite du plan de jeu."
et ne place pas le rocher/le monstre/la nourriture/l'équipement sur la carte. Le jeu continue normalement.
- Si aux coordonnées renseignées il y a déjà autre chose placée (un rocher, un monstre, de la nourriture,
un équipement, Rahan, Olivier) alors le programme renvoie comme warning :
"[WARNING] Impossible de placer le equipement. Autre chose est déjà présente aux coordonnées (x,y)." (avec x et y les valeurs
renseignés de l'utilisateur) et ne place pas le rocher/le monstre/la nourriture/l'équipement sur la carte. Le jeu continue normalement.

3) Gestion des erreurs:
- Si l'utilisateur donne en argument un fichier qui n'existe pas alors le programme renvoie comme erreur :
"[ERREUR] Erreur de lecture du ficher : " avec code d'erreur 1
Le programme s'arrête.
- Si l'utilisateur donne trop d'auguments alors le programme renvoie comme erreur :
"[ERREUR] Veuillez ne pas donner plus d'un fichier en argument." avec code d'erreur 2
Le programme s'arrête.
- Si l'entrée (entrée standard ou fichier) ne commence pas avec AUBE (ou A si format simple) alors le programme renvoie comme erreur :
"[ERREUR] Fichier ou Entree invalide! Il/Elle doit commencer par AUBE (ou A si format simple)." avec code d'erreur 3
Le programme s'arrête.
- Si l'entrée (entrée standard ou fichier) ne finie pas avec CREPUSCULE (ou C si format simple) alors le programme renvoie comme erreur :
"[ERREUR] Fichier ou Entree invalide! Il/Elle doit finit par CREPUSCULE (ou C si format simple)." avec code d'erreur 4
Le programme s'arrête.

4) IA :
Ma fonction d'IA "ivoire_albe()" (dans le fichier personnages.c) fonctionne de la manière suivante :
L'IA commence à regarder en haut de Rahan, puis continue de regarder autour de Rahan dans le sens des aiguilles d'une
montre. Si l'IA trouve un bonus (un bonus est soit de la nourriture, soit un équipement) alors l'IA va déplacer Rahan vers
ce bonus.
Si l'IA ne trouve pas de bonus autour de Rahan, alors l'IA va regarder si elle trouve un malus autour de Rahan (un malus est soit
un monstre, soit un rocher) en commencant par le haut, puis en continuant dans le sens des aiguilles d'une montre. Si l'IA trouve
un malus, alors l'IA va déplacer Rahan vers le côté opposé de ce malus.
Si l'IA ne trouve rien autour de Rahan, alors l'IA va déplacer Rahan par défaut vers le haut.
La vitesse de Rahan n'est pas prise en compte, l'IA va déplacer Rahan de seulement une case, peut importe sa vitesse.

5) Autre :
- Ce projet à été fait sur Windows 10 en utilisant WSL. Le programme se compile sans erreurs 
et s'exécute sans erreurs (en utilisant valgrind). Mes 7 fichiers de tests sont dans le répertoire test/. Sur votre site web
je n'ai pas trouvé de fichiers de votre part pour pouvoir tester mon programme. En effet il y a seulement écrit: 
"Parties interactives que votre programme doit savoir exécuter (par ordre de complexité) : À faire" (à la date du 21 Janvier
2024 à 17h30).
