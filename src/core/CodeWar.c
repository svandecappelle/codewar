#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "definitions.h"
#include "interpretor/interpretor.h"
#include "launch/modifications.h"


int main(int argc, char *argv[]){
  processeur liste_processeur[16][16];
  adresse j1,j2 ;
  int nbTours = 20;
  srand(time(NULL));


  j1.x = 0;
  j1.y = 0;

  j2.x = 0;
  j2.y = 1;

  creer_liste(liste_processeur,argc,argv,j1,j2,C1,C2);
  printf("Combien de tours de jeu voulez-vous ??\n");
  scanf("%d",&nbTours);

  jeu( liste_processeur, nbTours);

  controle_victoire(liste_processeur,*(short int *)&liste_processeur[j1.x][j1.y].ram[1],*(short int *)&liste_processeur[j2.x][j2.y].ram[1]);

  return 1;
}
