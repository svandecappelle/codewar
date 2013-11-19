#include "definitions.h"



/*traitement des opérandes source*/

unsigned short int get_registre_source( unsigned short int mot, processeur *p){
  return p->r[mot%8];
}

unsigned short int get_adressage_indirect_predecremente_source(unsigned short int mot, processeur *p){
  unsigned short int *retour;
  p->r[mot%8]-=2;
  retour = ( unsigned short int *)&p->ram[p->r[mot%8]&0x00FF];
  return *retour;
}


unsigned short int get_adressage_indirect_source( unsigned short int mot, processeur *p){
  unsigned short int *retour = (unsigned short int *)&p->ram[(p->r[mot%8]&0x00FF)];
  return *retour;
}

unsigned short int get_adressage_indirect_post_incremente_source(unsigned short int mot, processeur *p){
  unsigned short int *retour =  (unsigned short int *)&p->ram[p->r[mot%8]&0x00FF];
  p->r[mot%8]+=2;
  return *retour;
}

unsigned short int get_valeur_immediate_source( unsigned short int mot, processeur *p){
  return  mot;
}

unsigned short int get_adresse_memoire_source( unsigned short int mot, processeur *p){
  return mot&0x00FF;
}


/*Traitement des opérandes en destination*/



unsigned short int get_registre_dest( unsigned short int mot, processeur *p){
  return mot;
}

unsigned short int get_adressage_indirect_predecremente_dest(unsigned short int mot, processeur *p){
  p->r[mot%8]-=2;
  return p->r[mot%8]&0x00FF ;
}


unsigned short int get_adressage_indirect_dest( unsigned short int mot, processeur *p){
  return p->r[mot%8]&0x00FF;
}

unsigned short int get_adressage_indirect_post_incremente_dest(unsigned short int mot, processeur *p){
  unsigned short int retour = p->r[mot%8];
  p->r[mot%8]+=2;
  return retour&0x00FF;
}



