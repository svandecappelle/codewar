#include "definitions.h"
#include "commandes.h"
#include "modifications.h"
#include "affichage.h"
#include <unistd.h>
#include <gtk/gtk.h>
#include "argumentsGraphiques.h"

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
  rien,
  rte,
};



void jeu( processeur liste_processeur[][16], int nbTours, plateauGraphique * plateau){
  adresse ad;
  int x, y;
  processeur *p ;
  short int mot;
  GtkWidget *f;
 
  /* Tant qu'il reste des tours à effectuer*/

  while(nbTours > 0){
    /*on affiche le plateau de jeu*/
    affichage_gtk(liste_processeur,plateau);
    nbTours -= 1;

    /*on applique la liste des interruptions, et celles des modifications*/
    appliquer_interruptions(liste_processeur);
    appliquer_modifications(liste_processeur);

    /*on parcourt le plateau de jeu*/
    for(x = 0; x<16; x+=1){
      for(y = 0; y<16; y+=1){
	/*on initialise l'adresse du processeur courant*/
	ad.x = x;
	ad.y = y;
	ad.adresse_memoire = 0;


	/*on récupère le processeur courant pour que le code soit plus lisible*/
	p = & liste_processeur[ad.x][ad.y];
	
	/*on récupère le mot dans la mémoire ram du processeur*/
	mot = *(short int *)&p->ram[p->r[PC]%256];
	
	/*Si le processeur n'a pas joué (cas ou le processeur a levé une interruption ou été ciblé par un TRAP)*/
	if(!p->aJoue){

	  /*si le timer est actif*/
	  if(p->ram[TIMER_ACTIF]){
	    /*Si le timer n'est pas arrivé à expiration*/
	    if(p->ram[HORLOGE]<p->ram[VALEUR_LIMITE]){
	      /*si on detecte une instruction illegale*/
	      if(mot>>11==0x001F){
		/*on ajoute une interruption à la liste des interruptions qui sera exécutée le tour suivant*/
		ajouter_liste_interruption(&ad,ILLEGAL);
	      }
	      else{
		/*On appelle la commande associée à la commande décodée dans le mot*/
		tableau_de_commandes[((mot>>11)&0x1F)%30](liste_processeur,&ad);
		/*on met à jour le nombre de cycles effectués par le processeur*/
		p->cycles+=1;
		
		
		/*si ce nombre de cycle est supérieur au nombre de cycles limite inscrit dans la ram*/
		if(p->cycles >= p->ram[CYCLES]){
		  /*on incrémente l'horloge et on réinitialise le nombre de cycles à 0*/
		  p->ram[HORLOGE]+=1;
		  p->cycles = 0;
		}
	      }
	    }
	    else{
	      /*si le timer est arrivé à expiration on lève une interruption TIMER*/
	      ajouter_liste_interruption(&ad,TIMER);
	      /*On réinitialise la configuration du timer*/
	      p->ram[HORLOGE]=0;
	      p->ram[TIMER_ACTIF]=0;
	      p->cycles = 0;
	    }
	  }
	  else{
	    /*si le timer n'est pas actif, on se contente de contrôler si l'instruction est illégale, de lever une interruption le cas échéant
	      et de lancer la commande dans le cas contraire*/
	    if(mot>>11==0x001F){
	      ajouter_liste_interruption(&ad,ILLEGAL);
	    }
	    else{
	      tableau_de_commandes[((mot>>11)&0x1F%30)](liste_processeur,&ad);
	      /*On appelle la commande associée à la commande décodée dans le mot*/
	    }
	  }
	}
	else{
	  /*Si le processeur a déjà joué le tour courant on remet le flag à 0 pour le tour suivant*/
	  p->aJoue = 0;
	}
      }
      
    }
    /* on récupère la fenêtre en vue de la redessiner */
    f= (GtkWidget *)gtk_builder_get_object(plateau->plateau, "window1");
    gtk_widget_draw(f,NULL);    
  }
}
