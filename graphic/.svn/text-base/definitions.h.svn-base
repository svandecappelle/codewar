#ifndef DEFINITIONS_H
#define DEFINITIONS_H



/*definitions.h*/

/*definition des numéros de registre*/

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5

#define PC 6
#define SP 7
#define RE 8

/*definitions des bites du registre d'état*/

#define C 1
#define Z 2
#define N 4

/*definition du systeme d'adressage du timer*/

#define VALEUR_LIMITE 10
#define HORLOGE 11
#define CYCLES 12
#define TIMER_ACTIF 13


#define C1 45987
#define C2 8723

/*definition des types d'interruption*/
#define TIMER 4
#define ILLEGAL 3
#define TRAP 5

#define MASQUE 0xFFFF

#define TAILLE 16

typedef struct {
  unsigned short int r[8];
  unsigned char ram[256];
  unsigned int cycles ;
  unsigned char aJoue;
}processeur;

typedef struct {
  unsigned char x,y;
  unsigned char adresse_memoire; 
}adresse;

typedef struct liste_adresse{
  /*source de l'écriture    --> modifiée par exemple avec les registres post-incrémentés et pré-décrémentés*/
  /*cible de l'écriture*/
  adresse cible;         /*--> Adresse à comparer avec toutes les autres adresses d'écritures*/
  struct liste_valeur *listeVal;
  struct liste_adresse *suivant;
}liste_adresse;



typedef struct liste_valeur{
  unsigned char valeur;
  struct liste_valeur* suivant;
}liste_valeur;

typedef struct {
  unsigned int r:3;  
  unsigned int type_dest:3;
  unsigned int type_source:3;
  unsigned int l:1;
  unsigned int h:1;
  unsigned int commande:5;
  unsigned int val:16;
}mot_move;


typedef struct{
  unsigned int val:8;
  unsigned int type_source:3;
  unsigned int commande:5;
}mot_un_operande;

typedef struct{
  unsigned int val:5;
  unsigned int type_source:3;
  unsigned int reg_dest:3;
  unsigned int commande:5;
}mot_deux_operande;

typedef 
  union {
    unsigned short int tout ;
    struct {
      unsigned int x : 1 ;
      unsigned int r : 5 ;
      unsigned int v : 5 ;
      unsigned int b : 5 ;
    } composed ;
  }couleur_processeur;

#endif
