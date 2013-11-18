#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "definitions.h"
#include "commandes.h"
#include "modifications.h"
#include "debug.h"
#include "affichage.h"

/*Déclaration de la liste des commandes à exécuter*/
/*cette liste est contenue dans un tableau de pointeurs sur une commande*/
typedef void (* commandes)(processeur liste_processeur[][16],adresse *ad);


/* Le tableau de commandes qui regroupe toute les adresses de toutes les fonctions*/
commandes tableau_de_commandes[] = {
  move,
  push,
  pop,
  add,
  cmp,
  sub,
  lsl,
  lsr,
  and,
  or,
  xor,
  not,
  bcc_bgt,
  bcs_blt,
  beq,
  bne,
  ble,
  bge,
  bra,
  bsr,
  jcc_jgt,
  jcs_jlt,
  jeq,
  jne,
  jle,
  jge,
  jmp,
  jsr,
  rts,
  trap,
  rte,
};



void jeu( processeur liste_processeur[][16], int nbTours  ){
  adresse ad;
  int x, y;
  processeur *p ;
  short int mot;

    
  while(nbTours > 0){
    printf("tours restants  : %d\n\n",nbTours);
    nbTours -= 1;
    appliquer_interruptions(liste_processeur);
    appliquer_modifications(liste_processeur);
    afficher_plateau(liste_processeur,C1,C2);
    afficher_processeur_debug(liste_processeur[0][0]);

    for(x = 0; x<16; x+=1){
      for(y = 0; y<16; y+=1){
	ad.x = x;
	ad.y = y;
	ad.adresse_memoire = 0;
	p = & liste_processeur[ad.x][ad.y];
	mot = *(short int *)&p->ram[(p->r[PC])%256];

	/*Si le processeur n'a pas joué*/

	if(!p->aJoue){
	  /*si le timer est actif*/

	  if(p->ram[TIMER_ACTIF]){

	    /*Si le timer n'est pas arrivé à expiration*/
	    if(p->ram[HORLOGE]<p->ram[VALEUR_LIMITE]){
	      /*si on detecte une instruction illegale*/
	      if((mot>>11)==0x001F){
		ajouter_liste_interruption(&ad,ILLEGAL);
	      }
	      else{
		tableau_de_commandes[((mot>>11)&0x001F)%30](liste_processeur,&ad);
		/*On appelle la commande associée à la commande décodée dans le mot*/
		p->cycles+=1;
		if(p->cycles >= p->ram[CYCLES]){
		  
		  p->ram[HORLOGE]+=1;
		  p->cycles = 0;
		}
	      }
	    }
	    else{
	      
	      ajouter_liste_interruption(&ad,TIMER);
	      p->ram[HORLOGE]=0;
	      p->ram[TIMER_ACTIF]=0;
	      p->cycles = 0;
	    }
	  }
	  else{
	    /*si on detecte une instruction illegale*/
	    if((mot>>11)==0x001F){
	      ajouter_liste_interruption(&ad,ILLEGAL);
	    }
	    else{
	      tableau_de_commandes[((mot>>11)&0x001F)%30](liste_processeur,&ad);
	    }
	    /*On appelle la commande associée à la commande décodée dans le mot*/
	  }
	}
	else{
	  /*Si le processeur a déjà joué le tour courant on remet le flag à 0 pour le tour suivant*/
	  p->aJoue = 0;
	}
      
      }
    
    }
#ifndef WIN32
    sleep(1);
#endif

  }

  
  printf("tour final\n");
  afficher_plateau(liste_processeur,C1,C2);
}
