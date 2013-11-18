#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>
#include "definitions.h"




void afficher_processeur_debug(processeur p)
{
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


void creer_processeur_type(processeur *p)
{
  int i;
  for (i=0;i<256;i+=1){
    p->ram[i]=0xAA;
    
    if  (i<9){
      p->r[i]=187;
    }
  }
  
  p->ram[VALEUR_LIMITE] = 0;
  p->ram[HORLOGE]=0;
  p->ram[CYCLES] = 0;
  p->ram[TIMER_ACTIF]=0;
  p->cycles = 0;

  p->r[RE] = 2;
  p->r[PC] = 0x10;
  p->r[SP]=256;
  p->cycles = 0;
}


void test_commande(processeur *p, char *s){
  int fd = open(s,O_RDONLY);
  unsigned char *tmp ;
  if(fd==-1){
    printf("ouverture du fichier %s impossible\n",s);
  }
  else{
    tmp =  &p->ram[0x10];
    if(read(fd, tmp,256-(8*0x10))==-1){
      printf("Lecture du fichier %s impossible\n",s);
    }
    else{
      printf("\n\ntest de %s\n\n",s);
    }
  }


}
