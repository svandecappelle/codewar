#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "definitions.h"
#include "interpreteur.h"
#include "modifications.h"
#include "affichage.h"
#include "gtk/gtk.h"
#include "argumentsGraphiques.h"
#include "test2.h"


static GtkWidget *pLabel;
static GtkWidget *pWindow;
int Choix;


void FinJeuOK(GtkButton *bouton,GtkWidget *pWindow){
  
  gtk_widget_destroy(pWindow);
}



void choix_ok(GtkButton *bouton,GtkSpinButton *SpinButton){
  Choix =  gtk_spin_button_get_value_as_int((GtkSpinButton*)SpinButton);
  gtk_widget_destroy(pWindow);
}

void LancerBoite(void)
{
  GtkBuilder *unBuilder;
  GError      *  p_err       = NULL;
  GtkWidget *window;
  GtkSpinButton *bouton;
  
  
   /* Creation d'un nouveau GtkBuilder */
   unBuilder = gtk_builder_new ();

   if (unBuilder != NULL)
   {
      /* Chargement du XML dans unBuilder */
      gtk_builder_add_from_file (unBuilder, "nbTours.xml", & p_err);
      
      if (p_err == NULL)
      {
	
	
         /* Recuparation d'un pointeur sur la fenetre. */
	pWindow = (GtkWidget *) gtk_builder_get_object ((GtkBuilder*)unBuilder, "window1");

	 /* Signal du menu Nouveau Jeu */

	bouton = (GtkSpinButton*)gtk_builder_get_object ((GtkBuilder*)unBuilder, "BoutonNbTour");
	g_signal_connect (gtk_builder_get_object (unBuilder, "ok_button"),"clicked", G_CALLBACK (choix_ok),bouton);
	

	 g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
         gtk_widget_show_all (pWindow);
         gtk_main ();

      }
      else
      {
         /* Affichage du message d'erreur de GTK+ */
         g_error ("%s", p_err->message);
         g_error_free (p_err);
      }
   }
}

void affichage_fin_jeu(int joueur){


  GtkBuilder *unBuilder;
  GError      *  p_err       = NULL;
  GtkWidget *pWindow;
  
  
   /* Creation d'un nouveau GtkBuilder */
   unBuilder = gtk_builder_new ();

   if (unBuilder != NULL)
   {
      /* Chargement du XML dans unBuilder */
      gtk_builder_add_from_file (unBuilder, "FinJeu.xml", & p_err);
      
      if (p_err == NULL)
      {
	GtkLabel *label;
	
         /* Recuparation d'un pointeur sur la fenetre. */
	pWindow = (GtkWidget *) gtk_builder_get_object ((GtkBuilder*)unBuilder, "window1");

	label = (GtkLabel*)gtk_builder_get_object (unBuilder, "Resultat");
	



	if (joueur==1){
	  gtk_label_set_text(label,"Joueur 1 a gagne");
	}
	else if (joueur ==-1){
	  gtk_label_set_text(label,"Joueur 2 a gagne");
	}else{
	  gtk_label_set_text(label,"Match Nul");
	}

	 /* Signal du menu Nouveau Jeu */
	
         g_signal_connect (
			   gtk_builder_get_object (unBuilder, "ok_button"),
			   "clicked", G_CALLBACK (FinJeuOK), pWindow 
			   );
	

	 g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
         gtk_widget_show_all (pWindow);
         gtk_main ();

      }
      else
      {
         /* Affichage du message d'erreur de GTK+ */
         g_error ("%s", p_err->message);
         g_error_free (p_err);
      }
   } 
}

int main2(int argc, char *argv[],plateauGraphique *plateau){
  processeur liste_processeur[16][16];
  adresse j1,j2 ;
  int nbTours = 20;
  int x,y;
  char nomBouton[5],b[3];
  GtkColorButton *couleur1;
  GdkColor color;
  int couleur;
  srand(time(NULL));  
  j1.x = plateau->demarre[0].xy.x;
  j1.y = plateau->demarre[0].xy.y;
  j2.x = plateau->demarre[1].xy.x;
  j2.y = plateau->demarre[1].xy.y;
/*   printf("%s\n",argv[0]); */
/*   printf("%s\n",argv[1]); */
/*   printf("%s\n",argv[2]); */
  creer_liste(liste_processeur,argc,argv,j1,j2,plateau);
/*   printf("Combien de tours de jeu voulez-vous ??\n"); */
  LancerBoite();
 /*  printf("nbTour : %d\n",Choix); */
  jeu( liste_processeur, Choix,(plateauGraphique*)plateau);
  affichage_gtk(liste_processeur,plateau);
  affichage_fin_jeu(controle_victoire(liste_processeur,*(short int *)&liste_processeur[j1.x][j1.y].ram[1],*(short int *)&liste_processeur[j2.x][j2.y].ram[1]));
  
/*   for(x = 0; x<16; x+=1){ */
/*     for(y = 0; y<16; y+=1){ */
/*       couleur = liste_processeur[y][x].ram[1]; */
/*       if(x>9){ */
/* 	nomBouton[0] = '1'; */
/* 	nomBouton[1] = 48+(char)x%10; */
/*       } */
/*       else{ */
/* 	nomBouton[1] = 48+(char)x%10;	 */
/* 	nomBouton[0] = '0'; */
/*       } */
/*       nomBouton[2] = 0; */
      
/*       if(y>9){ */
/* 	b[0] = '1'; */
/* 	b[1] = (char)(48+y%10); */
/*       } */
/*       else{ */
/* 	b[1] = (char)(48+y%10);	 */
/* 	b[0] = '0'; */
/*       } */
/*       b[2] = 0; */
      
/*       strcat(nomBouton,b); */
/*       if (liste_processeur[y][x].ram[1]!=0){ */
/* /\* 	printf("Couleur : %d\n",liste_processeur[y][x].ram[1]); *\/ */
/* /\* 	printf("x = %d, y = %d, bouton : %s\n",x,y,nomBouton); *\/ */
	
/* 	couleur1 = (GtkColorButton *)gtk_builder_get_object(p_builder, nomBouton); */
/* 	color.red=0;  */
/* 	color.green=0;  */
/* 	color.blue=0;  */
/* 	gtk_color_button_set_color(couleur1,&color); */
/* 	liste_processeur[y][x].ram[1]=0; */
/*       } */
/*     } */
/*   } */
  
  return 1;
}
