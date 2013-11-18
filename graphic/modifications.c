#ifndef WIN32
/*headers � include sous windows*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#else

#include <unistd.h>
#include <time.h>
/*headers � inclure sous linux*/
#endif
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
#include "commandes.h"
#include "affichage.h"
#include "argumentsGraphiques.h"


liste_adresse * liste;
liste_adresse * liste_int;


/*compare deux adresses entre elles*/

int adrcmp(adresse *ad1, adresse *ad2){
  if(ad1->x ==ad2->x&& ad1->y== ad2->y&&ad1->adresse_memoire==ad2->adresse_memoire){
    return 0;
  }
  return 1;
}

/*va �crire en m�moire la liste des �critures associ�e � une adresse*/

void ecrire(liste_adresse * adresse,processeur liste_processeur[][TAILLE]){
  char val = 0;
  liste_valeur *tmp= adresse->listeVal,*f;

  /* si la liste de valeurs n'est pas vide*/
  if(tmp!=NULL){
    /*tant qu'on peut la parcourir*/
    while(tmp != NULL){
      /*on r�cup�re le maillon courant*/
      f = tmp;
      /*on ajoute sa valeur � la valeur � �crire*/
      val += tmp->valeur;
      /*on passe au maillon suivant et on lib�re le maillon utilis� pr�c�demment*/
      tmp = tmp->suivant;
      free(f);
    }
    /*On va �crire le r�sultat en m�moire � l'adresse correspondante*/
    liste_processeur[adresse->cible.x][adresse->cible.y].ram[adresse->cible.adresse_memoire] = val;
  }
}


/*va �crire en m�moire les �critures associ�es � une liste d'adresses*/
void appliquer_modifications(processeur  liste_processeur[][TAILLE]){
  liste_adresse *tmp;


  /*si la liste n'est pas vide*/
  if(liste!=NULL){
    /*traitement des n-1 premiers cas*/
    while(liste->suivant !=NULL){
      /*on va �crire les valeurs associ�es � l'adresse courante en m�moire*/
      ecrire(liste,liste_processeur);
      /*on r�cup�re le maillon courant*/
      tmp= liste;
      /*on passe � l'adresse suivante */
      liste = liste->suivant;
      /*on lib�re le maillon utilis� pr�c�demment*/
      free(tmp);
    }

    /*traitement du dernier cas */
    /*on �crit et on lib�re le maillon courant*/
    ecrire(liste,liste_processeur);
    free(liste);
    /*on r�initialise la liste � NULL par s�curit�*/
    liste = NULL;
  }
}

/*ajoute une valeur � �crire � une adresse donn�e*/

void ajouter_valeur(liste_adresse *adresse, char val){
  /*on r�cup�re la t�te de la liste de valeurs courante dans un tampon*/
  liste_valeur * tmp = adresse->listeVal;

  /* on alloue l'�l�ment suivant de la liste et on le place en t�te de la liste des valeurs � ajouter � l'adresse*/
  adresse->listeVal = (liste_valeur *)malloc(sizeof(liste_valeur));
  /*on initialise sa valeur*/
  adresse->listeVal->valeur = val;


  /*enfin on met le tampon � la suite de l'�l�ment qu'on vient d'allouer*/
  /*------------>  tmp est le second maillon de la liste*/
  adresse->listeVal->suivant = tmp;
}


/*ajoute une adresse et une valeur � �crire � la liste d'adresse*/
liste_adresse * ajouter_adresse(liste_adresse *tmp, adresse *ad, char val){
  /*On alloue le maillon de la liste d'adresse pass� en param�tre*/
  tmp = (liste_adresse*)malloc(sizeof(liste_adresse));
  
  if(tmp!=NULL){
    /*initialisation de l'adresse*/
    tmp->cible.x = ad->x;
    tmp->cible.y = ad->y;
    tmp->cible.adresse_memoire = ad->adresse_memoire;
    /*l'adresse suivante vaut null, la liste de Valeurs aussi*/
    tmp->suivant = NULL;
    tmp -> listeVal = NULL;
    /*on y ajoute une Valeur*/
    ajouter_valeur(tmp,val);
    /*on retourne le maillon ainsi cr��*/
    return tmp;
  }
  /*pour le compilateur on retourne NULL*/
  return NULL;
}

/*ajoute une valeur � une adresse donn�e dans la liste d'adresses*/

void ajouter_modification(adresse *ad, char val){
  liste_adresse *tmp;
  char attribue = 0;
  /*si la liste d'adresse est vide*/
  if(liste ==NULL){
    /*on ajoute le premier maillon de la liste*/
    liste = ajouter_adresse(liste,ad,val);
  }
  else{
    /*sinon on sauvegarde le maillon courant*/
    tmp = liste;
    /*traitement des n-1 premiers cas*/
    /*tant qu'on a un suivant*/
    while(tmp->suivant != NULL && !attribue){
      /*on compare l'adresse pass�e en param�tre � l'adresse courante*/
      if(adrcmp(ad,&tmp->cible)==0){
	/*si elles sont identiques on ajoute une valeur � la liste correspondante*/	  
	ajouter_valeur(tmp,val);
	/*on passe � l'adresse suivante*/
	tmp = tmp->suivant;
	/* on met le booleen attribue � 1*/
	attribue = 1;
      }
      tmp = tmp->suivant;
    }

    /*traitement du dernier cas*/
    /*si l'adresse est la m�me et que la valeur n'a pas �t� attribu�e*/
    if(adrcmp(ad,&tmp->cible)==0 && !attribue){
      /*on ajoute la valeur*/
      ajouter_valeur(tmp,val);
    }
    else{
      /*si la valeur n'a pas �t� attribu�e*/
      if(!attribue){
	/*on rajoute une adresse � �crire*/
	tmp->suivant = ajouter_adresse(tmp,ad,val);
      }
    }
  }
}


/*============================================= Gestion des interruptions =========================================*/



void appliquer_interruptions(processeur  liste_processeur[][TAILLE]){
  liste_valeur *tmp_int;
  liste_adresse * tmp_ad, *parcours;

  parcours = liste_int;

  /*si la liste d'interruptions n'est pas vide, on la parcourt */
  if(parcours!=NULL){
    while(parcours!= NULL){
      /*On marque le processeur cible pour signaler qu'il a jou� dans le tour courant*/
      liste_processeur[parcours->cible.x][parcours->cible.y].aJoue = 1;
      /*on applique la premi�re des interruptions associ�es � l'adresse*/
      interruption(&liste_processeur[parcours->cible.x][parcours->cible.y],&parcours->cible, parcours->listeVal->valeur);

      /* on lib�re l'interruption qui a �t� effectu�e*/
      tmp_int = parcours->listeVal;
      parcours->listeVal = parcours->listeVal->suivant;
      free(tmp_int);


      /*si l'adresse n'a plus d'interruptions qui lui sont associ�es on la lib�re*/
      if(parcours->listeVal == NULL){
	tmp_ad = parcours;
	parcours = parcours->suivant;

	/*si cette adresse est le d�but de la liste, on sauvegarde le nouveau d�but de la liste*/
	if(liste_int == tmp_ad){
	  liste_int = parcours;
	}

	/*on lib�re l'adresse*/
	free(tmp_ad);
      }
      else{
	/*sinon on continue le parcours normalement*/
	parcours = parcours->suivant;
      }
    }
  }
}


void ajouter_interruption(liste_adresse *tmp, char type){
  liste_valeur *nouveau = (liste_valeur*)malloc(sizeof(liste_valeur));
  nouveau->valeur = type;


  /*le TRAP a la priorit� sur les autres interruptions*/
  /* --> si l'interruption est un trap on la met en t�te de liste*/
  if(type == TRAP){
    nouveau->suivant = tmp->listeVal;
    tmp->listeVal = nouveau;
  }
  else{
    /*sinon on l'ajoute en queue*/
    nouveau->suivant = NULL;
    while(tmp->listeVal->suivant != NULL){
      tmp->listeVal = tmp->listeVal->suivant;
    }
    tmp->listeVal->suivant = nouveau;
  }

}



void ajouter_liste_interruption(adresse *ad, char type){
  liste_adresse *tmp;

  /*si la liste d'interruptions est vide, on la cr�e*/
  if(liste_int ==NULL){
    liste_int = ajouter_adresse(liste_int,ad,type);
  }
  else{
    /*sinon, on la parcourt pour trouver les adresses d�j� d�sign�es par une interruption*/
    tmp = liste_int;
    while(tmp->suivant != NULL){
      /* si on trouve une interruption � l'adresse voulue, on l'ajoute*/
      if(adrcmp(ad,&tmp->cible)==0){
	ajouter_interruption(tmp,type);
	tmp = tmp->suivant;
	break;
      }
      tmp = tmp->suivant;
    }

    /*analyse de la derni�re adresse*/
    if(adrcmp(ad,&tmp->cible)==0){
      ajouter_interruption(tmp,type);
    }
    else{
      /*si l'interruption est g�n�r�e sur une adresse inexistante on ajoute celle-ci � la liste*/
      tmp->suivant = ajouter_adresse(tmp,ad,type);
    }
  }
}



/*fonctions de cr�ation des processeurs */
void creer_processeur(processeur *p){
  int k;

  /*initialisation de la ram*/
  for(k=0;k<256;k+=1){
    p->ram[k] = 0x00;
  }

  /*initialisation des regitres*/
  for(k = 0;k<6;k+=1){
    p->r[k] = 0;
  }
  /*initialisation des attributs ajout�s � notre conception*/
  p->aJoue = 0;
  p->cycles = 0;

  /*�criture de l'instruction JMP #10 � l'adresse 0X10*/
  p->ram[0x10] = 0x10;
  p->ram[0x11] = 0xD4;
  /*initialisation du compteur de programme et du registre d'�tat*/
  p->r[PC] = 0x10;
  p->r[RE] = 0;
  
  /*d�sactivation du timer, et initialisation du registre de pile*/
  p->ram[TIMER_ACTIF]=0;
  p->r[SP] = 256;
}

void creer_joueur(processeur *p, char *fichier, unsigned int couleur){
  int i,j,k;
  unsigned char *tmp;

#ifndef WIN32
  int fd;
#else
  FILE* file;
#endif

  for(i=0;i<16;i+=1){
    for(j=0;j<16;j+=1){
      for(k=0;k<256;k+=1){
	p->ram[k] = 0xAA;
      }
    }
  }


  p->cycles = 0;
  p->r[SP] = 256;
  p->r[PC] = 0x10;
  p->ram[TIMER_ACTIF]=0;

/*   printf("Couleur choisi : %04X\n",couleur); */
  /* Entr�e de la couleur dans la RAM */
  p->ram[1] = couleur&0x00FF;
  p->ram[2] = (couleur&0xFF00)>>8;

 /*  printf("Couleur entree dans la ram processeur : %04X\n", *(unsigned short int *)&p->ram[1]); */


#ifndef WIN32
  /*code linux*/
  fd = open(fichier,O_RDONLY);

  if(fd==-1){
    printf("ouverture du fichier %s impossible\n",fichier);
  }
  else{
    tmp =  &p->ram[0x10];
    if(read(fd, tmp,256-(8*0x10))==-1){
       printf("Lecture du fichier %s impossible\n",fichier); 
    }
  }
  close(fd);
#else
   /*code Windows*/
  file = fopen(fichier,"r");

  /*if(file==NULL){
    printf("ouverture du fichier %s impossible\n",fichier);
  }
  else{*/
    tmp =  &p->ram[0x10];
    fgets(tmp,256-(8*0x10),file);
    if(ferror(file)==-1){
      printf("Lecture du fichier %s impossible\n",fichier);
    }
  /*}*/
  fclose(file);

#endif

}

void creer_liste(processeur liste_processeur[][16], int argc, char **argv, adresse ad1, adresse ad2,plateauGraphique *p){
  int x,y;

  for(x=0;x<16;x+=1){
    for(y = 0; y<16; y+=1){
      creer_processeur(&liste_processeur[x][y]);
    }
  }

  /*  printf(" la couleur creer liste  P1----------------> %04X\n\n\n\n\n\n\n",p->demarre[0].couleur); */
/*    printf(" la couleur creer liste P2-----------------> %04X\n\n\n\n\n\n\n",p->demarre[1].couleur); */

  if(argc==3){
    argv+=1;
    creer_joueur(&liste_processeur[ad1.x][ad1.y],*argv,p->demarre[0].couleur);
    argv+=1;
    creer_joueur(&liste_processeur[ad2.x][ad2.y],*argv,p->demarre[1].couleur);
  }
  else{
  /*   printf("Le nombre de joueurs doit �tre 2\n"); */
  }
}

int controle_victoire(processeur liste_processeur[][16],short c1, short c2){
  int scores[] = {0,0};
  int x,y;

  /*parcours du plateau*/
  for(x = 0; x<16; x+=1){
    for(y = 0; y < 16; y+=1){
      /*tant qu'il y a des joueurs et qu'on n'a pas trouv� la couleur*/
      if(*(short int *)&liste_processeur[x][y].ram[1] == c1){
	scores[0] +=1;
      }
      else{
	if(*(short int *)&liste_processeur[x][y].ram[1] == c2){
	  scores[1]+=1;
	}
      }
    }
  }

  if(scores[0]>scores[1]){
/*     printf("Le joueur 1 a gagne\n"); */
    return 1;
  }
  else{
    if(scores[0]<scores[1]){
/*       printf("Le joueur 2 a gagne\n"); */
      return -1;
    }
    else{
/*       printf("Match nul !\n"); */
      return 0;
    }
  }
}

