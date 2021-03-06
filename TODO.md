Nous allons nous servir de ce fichier pour nous communiquer les diff�rents objectifs � atteindre, le travail fait et � faire.

# FAIT GRAPHIQUE
- suppr�sion du warning de compilation variable extern ;)
- Avanc� un peu sur le rapport.

# A FAIRE...
- signal du bouton "Cancel" dans la fenetre de choix nombre de tours.
- renvoi de GTK_main apres chaque tour de boucle, pour redonner la main a gtk et ainsi permetre de fermer la fenetre a chaque fin de boucle (tester et c'est pas facile a faire ;) )
- Fin du rapport avec les Annexes

---
 
# FAIT
- Edition de la structure du processeur
- Conversion d'une valeur cod�e sur 4 bits en d�cimal (utile pour l'adressage plateau de jeu)
- Mise en place du squelette de la gestion des op�randes (tests � effectuer)
- Mise en place du squelette de la gestion des commandes.
- Codage d'une commande en exemple de ce qui doit �tre cod�
- Liste des commandes DEJA cod�es : 

	- MOVE
	- PUSH
	- POP
	- ADD
	- CMP
	- SUB
	- LSL	
	- LSR
	- AND
	- OR
	- XOR
	- ...
	- BXX

- Commande travaill�e actuellement par Gr�g : BSR
- Commande travaill�e actuellement par Steeve : 
- Commenter encore plus le code ...
- Conception de la gestion de la m�moire
- Gestion des timers
- Gestion des interruptions
- Recopie d'un fichier binaire dans la ram d'un processeur
- Gestion de la dynamique du jeu

## Compiler : 

Un Makefile a �t� cr��, pour compiler il suffit de taper la commande "make" dans le r�pertoire ou sont situ�es les sources et le Makefile du projet

## D�composition du projet : 

Le projet sera divis�e en plusieurs parties
	- la dynamique du jeu en (g�r�e par le source CodeWar.c), 
	- la gestion des commandes (commandes.c)
	- la gestion de l'interpr�teur de commande (interpreteur.c)
	- la gestion de la m�moire (memoire.c)
	- la gestion des op�randes et des adresses (arguments.c)
	- la gestion type d'op�rande (typage_operande.c)

	il est possible que cette structure �volue, nous rajouterons alors des parties (si n�cessaire pour la gestion du timer ou des interruptions.

	Nous devrons commencer par programmer la gestion de la m�moire, qui est � la base de notre projet, puis nous remonterons : 
	1) gestion m�moire
	2) arguments
	3) commandes
	4) interpr�teur (d�j� fait, cas � part, cette partie nous permet de tester le programme depuis codewar, nous �viterons ainsi tous les d�sagr�ments d� � l'inclusion infinie de headers )
		cette partie a �t� programm�e gr�ce � un tableau de pointeurs sur les fonctions de type commande)


	5) Gestion des cas particuliers : interruptions, Timer, Move si c'est pas d�j� fait
	6) CodeWar, le jeu, le vrai :D
	
---

## Gestion de la m�moire, remarques :

	La m�moire du processeur est compos�e de 7 registres (plus le registre d'�tat) et 256 octets de RAM. La gestion de cette m�moire va r�sider dans la mani�re de faire transiter l'information provenant d'un registre, d'une constante inscrite dans le programme, ou encore d'une valeur de la pile dans la m�moire � une adresse donn�e.

	L'attribution du mode d'adressage ne sera pas trait�e dans cette partie du projet, mais dans la partie "operandes" (on r�cup�re une adresse au m�me moment dans la dynamique du programme ---> juste avant la cr�ation de l'�criture, au niveau de la commande)

---

## Partie "interpr�teur de commandes" :

	Dans cette partie, nous avons juste eu � interpr�ter les 5 bits de poids fort du mot se trouvant � l'adresse PC de la ram du processeur. Nous avons ici opt� pour la solution des pointeurs de fonction, sur des fonctions de type :

	short int (*commande)(short int pc, adresse *ad, processeur *p);

	Dans cette partie se trouvera aussi la fonction qui appliquera les �critures aux processeurs concern�s, ainsi le programme CodeWar n'aura jamais � acc�der directement ni � la m�moire, ni aux commandes.

	Dans la conception actuellement active, il suffit d'appeler 
		- get_instruction(0,ad,p) pour tomber sur le move,
		- get_instruction(1,ad,p) pour tomber sur le push, et ainsi de suite


## Dynamique de cr�ation d'une �criture : 

### I/
CodeWar appelle la fonction get_ecriture(short int pc, adresse *ad, processeur *p)  //contenu dans interpreteur.c

interpreteur  appelle une des commandes d�sign�es par le tableau de pointeur de fonction, le type des commandes est : 

	short int (*commande)(short int pc, adresse *ad, processeur *p)


### II/
La commande appel�e cr�e une ecriture en m�moire � l'aide d'un malloc

	ecriture e = (ecriture)malloc(1*sizeof(ecriture));  //Je me r�serve en m�moire la place d'une �criture ...


	La commande va ensuite se charger de compl�ter cette �criture par une valeur (op�rande d�cod�e), et une adresse (adresse d�cod�e)

	A noter que la lib�ration de cet espace m�moire n'est pas de la responsabilit� de la commande, mais du jeu (CodeWar) qui demande la cr�ation d'une �criture en appelant la commande.

Un free(ma_variable_ecriture) sera donc pratiqu� � chaque fois qu'une �criture sera appliqu�e (application de l'�criture en dur dans la m�moire) ou rejet�e (cas ou deux processeurs veulent �crire au m�me endroit).


### III/
la commande appel�e va appeler une fonction du type :
	contenue dans  arguments.c

	```short int get_operande_N(short int mot)```   
	o� 0<=N<=2 avec 0 pour le MOVE
    1 pour les commandes � une op�rande
	2 pour les commandes � deux op�randes


cette operande sera stock�e dans l'attribut valeur de l'�criture (   e->valeur = get_operande_N(mot)    )


### IV/
Cette fonction va alors appeler une fonction dy type :	//contenue dans typage_operande.c

	```
	short int (*operande)(short int mot)
	```

	(similaire � ce qui a �t� fait pour la partie interpr�teur de commande)

### V/
	La gestion de l'adressage est cod�e dans la partie arguments.c, nous consid�rons ici qu'� notre niveau, une adresse est un argument. 

## Fonction d�j� cod�e

## Partie jeu :

	Cette partie aura pour but de faire tourner 256 processeurs en parall�le. Parmi ces 256 processeurs, deux seront choisis al�atoirement pour se battre entre eux.

	Nous reviendrons sur cette partie quand nous aurons avanc� dans le projet.


