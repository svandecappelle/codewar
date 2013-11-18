#include "definitions.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include "test2.h"
#include "argumentsGraphiques.h"

void affichage_gtk(processeur liste_processeur[][16], plateauGraphique *plateau){
  sleep(1/2);
  int x,y;
  char nomBouton[5],b[3];
  GtkColorButton *couleur1;
  GdkColor color;
  int couleur;
  couleur_processeur mixer;
  GtkWidget *f;
/*   liste_processeur[0][0].ram[1]=217; */
/*   liste_processeur[0][1].ram[1]=17; */
  int nbTour = 0;
  for(x = 0; x<16; x+=1){
    for(y = 0; y<16; y+=1){
      couleur = liste_processeur[y][x].ram[1];
      if(x>9){
	nomBouton[0] = '1';
	nomBouton[1] = 48+(char)x%10;
      }
      else{
	nomBouton[1] = 48+(char)x%10;	
	nomBouton[0] = '0';
      }
      nomBouton[2] = 0;
      
      if(y>9){
	b[0] = '1';
	b[1] = (char)(48+y%10);
      }
      else{
	b[1] = (char)(48+y%10);	
	b[0] = '0';
      }
      b[2] = 0;
      strcat(nomBouton,b);
      mixer.tout = *(unsigned short int *)&liste_processeur[y][x].ram[1];
      couleur = mixer.tout;
      /* 	printf("\n\n\n\n"); */
      /* /\*  	printf("Couleur red: %d, green: %d, blue: %d\n", mixer.composed.r*8, mixer.composed.v*8, mixer.composed.b*8); *\/ */
      /*  	printf("Couleur BitField: %04X\n",mixer.tout) ; */
      /*  	printf("Couleur : %04X\n", *(unsigned short int *)&liste_processeur[y][x].ram[1]); */
      /* 	printf("x = %d, y = %d, bouton : %s\n",x,y,nomBouton); */
      f= (GtkWidget *)gtk_builder_get_object(p_builder, "window1");	
      couleur1 = (GtkColorButton *)gtk_builder_get_object(p_builder, nomBouton);
      if (couleur1 != NULL) {
	/* 	  gtk_widget_draw((GtkWidget *)couleur1,NULL);  */
	
	/*  if (mixer.tout !=0 || nbTour == 0) { */
	/* 	    printf("Couleur color button : red %d green: %d blue %d\n",color.red,color.green,color.blue); */
	/* 	    printf("Couleur red: %d, green: %d, blue: %d\n", mixer.composed.r, mixer.composed.v, mixer.composed.b); */
	
	color.red=(mixer.composed.r)<<11;
	color.green=(mixer.composed.v)<<11;
	color.blue=(mixer.composed.b)<<11;
	gtk_color_button_set_color(couleur1,&color);
	/* 	    printf("Couleur hexa : %04X\n",mixer.tout);  */
	/* } */
      }
    }
  }
}

void afficher_processeur(processeur p){
  int n;
  int i;

  printf("processeur\n");
  printf("Les Registres :\n");
  for (i=0;i<9;i+=1){
    switch(i){
    case PC:
      printf("PC = %04X\n",p.r[i]);
      break;
    case SP:
      printf("SP = %04X\n",p.r[i]);
      break;
    case RE:
      printf("RE = %04X\n",p.r[i]&0x07);
      break;
    default:
      printf("R[%d] = %04X \n",i,p.r[i]);
    }
  }

  printf("Cycle : %04X\n", p.cycles);
  printf("Horloge : %04X, limite : %04X\n",p.ram[HORLOGE], p.ram[VALEUR_LIMITE]);
  printf("___________________________________________________\n");
  printf("    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F \n___________________________________________________\n");
  for (i=0;i<16;i+=1){
    printf("%0x   ",i);
    for (n=0;n<16;n+=1){
      printf("%02x ",p.ram[i*16+n]);
    }
    printf("\n");
  }
  printf("\n");
}

void afficher_plateau(processeur liste_processeur[][TAILLE],short int c1, short int c2,GtkBuilder *plateau){
  int x,y;
/*   affichage_gtk(liste_processeur,plateau); */
  for(y = 0;y<16;y+=1){
    for(x = 0;x<16;x+=1){
      printf("|");
      printf("p : %d C1 : %d\n",*(short int *)&liste_processeur[x][y].ram[1],C1);
      if(*(short int *)&liste_processeur[x][y].ram[1]==c1){
	printf("R");
      }
      else{
	if(*(short int *)&liste_processeur[x][y].ram[1]==c2){
	  printf("V");

	}
	else{
	  printf(" ");
	}
      }
    }
    printf("|\n");
  }
}
