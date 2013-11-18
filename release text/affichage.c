#include <stdio.h>
#include "definitions.h"



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

void afficher_plateau(processeur liste_processeur[][TAILLE],short int c1, short int c2){
  int x=0,y=0;
  

  for(y = 0;y<16;y+=1){
    for(x = 0;x<16;x+=1){
      printf("|");
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
