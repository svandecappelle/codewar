#ifndef WIN32

/*headers à inclure uniquement sous windows*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#else

/*headers à inclure uniquement sous linux*/

#include <time.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../definitions.h"
#include "../interpretor/commands.h"



liste_adresse * liste;
liste_adresse * liste_int;


/*compare deux adresses entre elles*/

int adrcmp(adresse *ad1, adresse *ad2){
  if(ad1->x ==ad2->x&& ad1->y== ad2->y&&ad1->adresse_memoire==ad2->adresse_memoire){
    return 0;
  }
  return 1;
}

/*va écrire en mémoire la liste des écritures associée à une adresse*/

void ecrire(liste_adresse * adresse,processeur liste_processeur[][TAILLE]){
  char val = 0;
  liste_valeur *tmp= adresse->listeVal,*f;

  if(tmp!=NULL){
    while(tmp != NULL){
      f = tmp;
      val += tmp->valeur;
      tmp = tmp->suivant;
      free(f);
    }


    liste_processeur[adresse->cible.x][adresse->cible.y].ram[adresse->cible.adresse_memoire] = val;

  }
}


/*va écrire en mémoire les écritures associées à une liste d'adresses*/
void appliquer_modifications(processeur  liste_processeur[][TAILLE]){
  liste_adresse *tmp;

  if(liste!=NULL){
    /*traitement des n-1 premiers cas*/
    while(liste->suivant !=NULL){
      ecrire(liste,liste_processeur);
      tmp= liste;
      liste = liste->suivant;
      free(tmp);
    }

    /*traitement du dernier cas */
    ecrire(liste,liste_processeur);
    free(liste);

    liste = NULL;
  }
}

/*ajoute une valeur à écrire à une adresse donnée*/

void ajouter_valeur(liste_adresse *adresse, char val){
  liste_valeur * tmp = adresse->listeVal;

  adresse->listeVal = (liste_valeur *)malloc(sizeof(liste_valeur));
  adresse->listeVal->valeur = val;

  if(tmp!=NULL){
    adresse->listeVal->suivant = tmp;
  }
  else{
    adresse->listeVal->suivant = NULL;
  }
}


/*ajoute une adresse et une valeur à écrire à la liste d'adresse*/
liste_adresse * ajouter_adresse(liste_adresse *tmp, adresse *ad, char val){
  tmp = (liste_adresse*)malloc(sizeof(liste_adresse));
  if(tmp!=NULL){
    tmp->cible.x = ad->x;
    tmp->cible.y = ad->y;
    tmp->cible.adresse_memoire = ad->adresse_memoire;
    tmp->suivant = NULL;
    tmp -> listeVal = NULL;
    ajouter_valeur(tmp,val);
    return tmp;
  }
  return NULL;
}

/*ajoute une valeur à une adresse donnée dans la liste d'adresses*/

void ajouter_modification(adresse *ad, char val){
  liste_adresse *tmp;

  if(liste ==NULL){
    liste = ajouter_adresse(liste,ad,val);
  }
  else{
    tmp = liste;
    while(tmp->suivant != NULL){
      if(adrcmp(ad,&tmp->cible)==0){
	ajouter_valeur(tmp,val);
	tmp = tmp->suivant;
	break;
      }
      tmp = tmp->suivant;
    }

    if(adrcmp(ad,&tmp->cible)==0){
      ajouter_valeur(tmp,val);
    }
    else{
      tmp->suivant = ajouter_adresse(tmp,ad,val);
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
      /*On marque le processeur cible pour signaler qu'il a joué dans le tour courant*/
      liste_processeur[parcours->cible.x][parcours->cible.y].aJoue = 1;
      /*on applique la première des interruptions associées à l'adresse*/
      interruption(&liste_processeur[parcours->cible.x][parcours->cible.y],&parcours->cible, parcours->listeVal->valeur);
      printf("interruption\n");
      /* on libère l'interruption qui a été effectuée*/
      tmp_int = parcours->listeVal;
      parcours->listeVal = parcours->listeVal->suivant;
      free(tmp_int);


      /*si l'adresse n'a plus d'interruptions qui lui sont associées on la libère*/
      if(parcours->listeVal == NULL){
	tmp_ad = parcours;
	parcours = parcours->suivant;

	/*si cette adresse est le début de la liste, on sauvegarde le nouveau début de la liste*/
	if(liste_int == tmp_ad){
	  liste_int = parcours;
	}

	/*on libère l'adresse*/
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


  /*le TRAP a la priorité sur les autres interruptions*/
  /* --> si l'interruption est un trap on la met en tête de liste*/
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

  /*si la liste d'interruptions est vide, on la crée*/
  if(liste_int ==NULL){
    liste_int = ajouter_adresse(liste_int,ad,type);
  }
  else{
    /*sinon, on la parcourt pour trouver les adresses déjà désignées par une interruption*/
    tmp = liste_int;
    while(tmp->suivant != NULL){
      /* si on trouve une interruption à l'adresse voulue, on l'ajoute*/
      if(adrcmp(ad,&tmp->cible)==0){
	ajouter_interruption(tmp,type);
	tmp = tmp->suivant;
	break;
      }
      tmp = tmp->suivant;
    }

    /*analyse de la dernière adresse*/
    if(adrcmp(ad,&tmp->cible)==0){
      ajouter_interruption(tmp,type);
    }
    else{
      /*si l'interruption est générée sur une adresse inexistante on ajoute celle-ci à la liste*/
      tmp->suivant = ajouter_adresse(tmp,ad,type);
    }
  }
}



/*fonctions de création des processeurs */
void creer_processeur(processeur *p){
  int k;

  for(k=0;k<256;k+=1){
    p->ram[k] = 0xFF;
  }

  for(k = 0;k<6;k+=1){
    p->r[k] = 0;
  }
  p->aJoue = 0;
  p->cycles = 0;
  p->ram[0x10] = 0x10;
  p->ram[0x11] = 0xD4;
  p->r[PC] = 0x10;
  p->r[RE] = 0;
  p->ram[TIMER_ACTIF]=0;
  p->r[SP] = 256;
}

void creer_joueur(processeur *p, char *fichier, short int couleur){
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
	p->ram[k] = 0xFF;
      }
    }
  }


  p->cycles = 0;
  p->r[SP] = 256;
  p->r[PC] = 0x10;
  p->ram[TIMER_ACTIF]=0;
  p->ram[1] = couleur;
  p->ram[2] = (couleur>>8)&0x00FF;


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

void creer_liste(processeur liste_processeur[][16], int argc, char **argv, adresse ad1, adresse ad2){
  int x,y;

  for(x=0;x<16;x+=1){
    for(y = 0; y<16; y+=1){
      creer_processeur(&liste_processeur[x][y]);
    }
  }

  if(argc==3){
    argv+=1;
    creer_joueur(&liste_processeur[ad1.x][ad1.y],*argv, C1);
    argv+=1;
    creer_joueur(&liste_processeur[ad2.x][ad2.y],*argv, C2);
  }
  else{
    printf("Le nombre de joueurs doit etre 2\n");
    exit(1);
  }
}

int controle_victoire(processeur liste_processeur[][16],short c1, short c2){
  int scores[] = {0,0};
  int x,y;

  /*parcours du plateau*/
  for(x = 0; x<16; x+=1){
    for(y = 0; y < 16; y+=1){
      /*tant qu'il y a des joueurs et qu'on n'a pas trouvé la couleur*/
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
    printf("Le joueur 1 a gagne\n");
    return 1;
  }
  else{
    if(scores[0]<scores[1]){
      printf("Le joueur 2 a gagne\n");
      return -1;
    }
    else{
      printf("Match nul !\n");
      return 0;
    }
  }
}

