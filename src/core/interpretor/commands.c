#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "../launch/modifications.h"
#include "../definitions.h"
#include "arguments.h"
#include "flags.h"

/*################################### gestion des interruptions ############################################"*/

void ecrire_deux_octets(adresse *ad, unsigned short int val){
  ajouter_modification(ad,(val&0x00FF));
  ad->adresse_memoire +=1;
  ajouter_modification(ad,((val&0xFF00)>>8));
}



/*COMMANDES TESTEES*/

void empiler(processeur *p, adresse *ad, unsigned short int valeur){
  /*mise � jour de SP*/
  if(p->r[SP]>=2){
    p->r[SP]-=2;
    /*mise � jour de l'adresse � �crire*/
    ad->adresse_memoire = p->r[SP];
    /*�criture des valeur*/
    ecrire_deux_octets(ad,valeur);
  }
  else{
    printf("plus assez d'espace pour empiler\n");
  }

}


void interruption (processeur *p,adresse *ad, unsigned char type){
  /*empilement de la prochaine instruction*/
  empiler(p,ad,(short int)p->r[PC]+2);
  
  /*empilement du registre d'�tat*/
  empiler(p,ad,(short int)p->r[RE]);

  p->r[PC] = p->ram[type];
}


void trap( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  unsigned short int source;

  printf("trap\n");
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if(mot.val&0x8){                  /*si le mot d�cod� est une valeur n�gative*/
      ad->x+= mot.val&0xFF;          /*on d�cale de 12 bits et on masque avec OxFF de mani�re � obtenir une expression du                                        type 1111XXXX*/
    }
    else{
      ad->x+= mot.val >> 12;              /*Sinon on d�cale uniquement*/
    }
    
    if(mot.val &0x08){               /*Si le mot d�cal� est une valeur n�gative*/
      ad->y+= mot.val&0x0F;           /*on d�cale sur 8 bits, on isole les bits de position Y en masquant*/
      ad->y+= 0xF0;            /*enfin on ajoute F aux 4 bits de poids fort, de mani�re � obtenir une valeur du type                                       1111YYYY*/
    }
    else{
      ad->y+= mot.val &0x0F;          /*Sinon on d�cale uniquement la valeur sur 8 bits en la masquant*/
    }
    
    printf("x : %d, y : %d, mem : %d\n", ad->x, ad->y, ad->adresse_memoire);
    ajouter_liste_interruption(ad,TRAP);
  }
  printf("D'oh!\n");
}


void rts( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];

  /*commande test�e*/
  if(p->r[SP]<256){
    p->r[PC]=p->ram[p->r[SP]%256];
    p->r[SP]+=2;
  }
  else{
    p->r[PC]+=2;
    interruption (p,ad, ILLEGAL);
  }
}


/*#########################Commandes d'�criture en m�moire###########################################*/
 
void move(processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_move mot = *(mot_move*)&p->ram[p->r[PC]%256];
  unsigned short int source;
  unsigned short int dest ;

  
  printf("mot : %08X\n",*(int *)&p->ram[p->r[PC]]);  
  printf("source : %d\n",mot.type_source);
  printf("dest : %d\n",mot.type_dest);
  printf("MOVE : PC : %04X\n",p->r[PC]);
  printf("p->r[1] = %04X\n",p->r[1]);


  if( mot.type_source&0x0004){
    /*si la source est une valeur imm�diate ou une adresse*/
    if( get_operande_source_0(p,ad,mot,&source)){
      get_operande_dest_0(p,ad,mot,&dest);

      /*traitement associ� aux adressages par registre*/
      if( mot.type_dest !=0){
	ad->adresse_memoire = dest;
	ecrire_deux_octets(ad,source);
      }
      else{
	/*Si la destination est un registre*/
	p->r[dest%8] = source;
      }
    }
    MAJ_flags_move(p,source,2*mot.h+mot.l);
    p->r[PC]+=4;
  }
  else{
    /*si la source provient d'un registre*/
    if(get_operande_source_0(p,ad,mot,&source)){
      if( mot.type_dest==0x05){ /*si la destination est une adresse directe*/
	get_adresse(mot.val, ad);
	ecrire_deux_octets(ad,source);
      }
      else{
	if(mot.type_dest!=0){
	  /*si la destination n'est pas un registre, c'est un adressage indirect */
	  get_operande_dest_0(p,ad,mot,&dest);
	  ad->adresse_memoire = dest;
	  ecrire_deux_octets(ad,source);
	}
	else{
	  /*si la destination est un registre*/
	  get_operande_dest_0(p,ad,mot,&dest);
	  /*ICI*/
	  p->r[dest%8] = source;
	}
      }
    
      MAJ_flags_move(p,source,2*mot.h+mot.l);
    }
    p->r[PC]+=4;
  }
  printf("p->r[1] = %04X end\n",p->r[1]);
}

void push( processeur liste_processeur[][16], adresse *ad){

  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("push");
  if(get_operande_source_1(p,ad,mot,&source) ){

    empiler(p,ad,source);
    p->r[PC]+=2;
    MAJ_flags_move(p,source,0x03);  /*m�me type de mise � jour des flags que pour le move*/
  }
}


void pop( processeur liste_processeur[][16], adresse *ad){

  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  unsigned short int dest;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("pop\n");
  if(get_operande_dest_1(p,ad,mot,&dest)){
  /*r�cup�ration de la valeur des op�rande*/
    source = (unsigned short int )p->ram[p->r[SP]%256];
    
    /*traitement de ces valeurs*/
    if(mot.type_source!=0){
      ad->adresse_memoire = dest;
      /*si la destination est une adresse indirecte*/
      ecrire_deux_octets(ad,source);
    }
    else{
      /*si la destination est un registre*/
      p->r[dest%8] = source;
      /*on r�cup�re la valeur en m�moire associ�e au sommet de la pile*/
    }
    MAJ_flags_move(p,source,0x02);  /*m�me type de mise � jour des flags que pour le move*/
    p->r[SP]+=2;  /*mise � jour de SP*/
    p->r[PC]+=2;  /*mise � jour de PC*/
  }
}

/*##########################################Commandes arithm�tiques###############################################*/

void add( processeur liste_processeur[][16], adresse *ad){
  
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256];  
  unsigned short int val;
  unsigned short int numregistre;
  printf("ADD : PC : %04X\n",p->r[PC]);
  printf("p->r[1] = %04X\n",p->r[1]);
    
  if(get_operande_source_2(p,ad,mot,&val)){
    /* on peut faire les modifications sur le registre destination*/
    get_operande_dest_2(p,ad,mot,&numregistre);
    printf("val : %d\n",val);
    p->r[numregistre%8]+=val;
    p->r[PC]+=2;
  }
  printf("p->r[1] = %04X\n",p->r[1]);
}

void cmp( processeur liste_processeur[][16], adresse *ad){
 
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256];
  unsigned short int source;
  unsigned short int dest;
  printf("cmp\n");  
  if(get_operande_source_2(p,ad,mot,&source)){
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/
    get_operande_dest_2(p,ad,mot,&dest);
    dest = p->r[dest%8];
    source = dest - source;
    
    MAJ_flags_cmp_sub(p,source);
    p->r[PC]+=2;
  }
}

void sub( processeur liste_processeur[][16], adresse *ad){
 
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256];
  unsigned short int source;
  unsigned short int dest;
  printf("sub\n");
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/

  if(get_operande_source_2(p,ad,mot,&source)){
    get_operande_dest_2(p,ad,mot,&dest);
    p->r[dest%8] = p->r[dest%8]-source;

    MAJ_flags_cmp_sub(p,source);
    p->r[PC]+=2;
  }
}

/*###################################### commandes de d�calage de bits ###############################################*/

void lsl( processeur liste_processeur[][16], adresse *ad){
  
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256];
  unsigned short int source;
  unsigned short int dest;
  int masque;
  printf("lsl\n");
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/
  if(get_operande_source_2(p,ad,mot,&source)){
    get_operande_dest_2(p,ad,mot,&dest);
    /*si le d�calage � effectuer est inf�rieur � 16 bits*/
    if(source<=16){
      masque = 0;
      /*on d�cale la destination*/
      p->r[dest%8] = (p->r[dest%8]<<source);
	
      /*on calcule la valeur sur laquelle on va masquer la destination*/
      for(;source>0;source-=1){
	masque += pow(2,source-1);
      }
      
      /*La valeur de masquage vaut 0xFFFF-(somme des puissances de 2 des n bits d�cal�s)*/
      masque = MASQUE-masque;
      /*on masque la destination de mani�re � obtenir une valeur coh�rente*/
      p->r[dest%8] = p->r[dest]&masque;
      }
    else{
      /*si le nombre de bits � d�caler est sup�rieur � la longueur du registre, le resultat vaut 0*/
      p->r[dest%8] = 0;
    }
    MAJ_flags_ls(p,source,p->r[dest%8]);
    p->r[PC]+=2;
  }
}


void lsr( processeur liste_processeur[][16], adresse *ad){
 
  processeur *p = &liste_processeur[ad->x][ad->y];
  
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256];
  unsigned short int source;
  unsigned short int index;
  unsigned short int dest;
  int masque;
  printf("lsr\n");
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/
  if(get_operande_source_2(p,ad,mot,&source)){
    index = source;
    get_operande_dest_2(p,ad,mot,&dest);
    

    /*si le nombre de bits � d�caler est inf�rieur � 16*/

    if(source<=16){
      masque = 0;
      /*on d�cale la destination*/
      p->r[dest%8] = (p->r[dest%8]>>source);
      
      /*r�affectation de la source pour calcul du masquage
	la valeur de masquage est calcul�e sur la somme des n bits de poids fort d�cal�s */
	
      source = 15-source;
     
      for(;source>0;source-=1){
	masque += pow(2,source);
      }
      masque +=1;
      /*masquage de la destination de mani�re � obtenir une valeur coh�rente*/
      p->r[dest%8] = p->r[dest%8]&masque;      
    }
    else{
      /*si le nombre de bits � d�caler est sup�rieur � la longueur du registre, le resultat vaut 0*/
      p->r[dest%8] = 0;
    }
    /*mise � jour des flags et du compteur de programme*/
    MAJ_flags_ls(p,index,p->r[dest%8]);
    p->r[PC]+=2;
  }
}


/*################################### Commandes logiques #############################################*/



void and( processeur liste_processeur[][16], adresse *ad){
 
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256]; 
  unsigned short int source;
  unsigned short int dest;
  printf("and\n");
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/
  if(get_operande_source_2(p,ad,mot,&source)){
    get_operande_dest_2(p,ad,mot,&dest);
    /*r�cup�ration de la position du bit de poids fort le plus �lev� des des deux mots*/
  
    p->r[dest%8] = p->r[dest%8]&source;
    
    /*Mise � jour des flags et du compteur de programme*/
    MAJ_flags_logique(p,p->r[dest%8]);
    p->r[PC]+=2;
  }  

}

void or( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256]; 
  unsigned short int source;
  unsigned short int dest;
  
  printf("or\n");
  
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/
 
  if(get_operande_source_2(p,ad,mot,&source)){
    get_operande_dest_2(p,ad,mot,&dest);

    p->r[dest%8] = p->r[dest%8]|source;
    
    /*Mise � jour des flags et du compteur de programme*/
    MAJ_flags_logique(p,p->r[dest%8]);
    p->r[PC]+=2;
  }  


}


void xor( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_deux_operande mot= *(mot_deux_operande *)&p->ram[p->r[PC]%256]; 
  unsigned short int source;
  unsigned short int dest;
  printf("xor\n");
  /*r�cup�ration de la valeur de la source et du num�ro de registre D*/
  if(get_operande_source_2(p,ad,mot,&source)){
    get_operande_dest_2(p,ad,mot,&dest);
   
    p->r[dest%8] = p->r[dest%8]^source;
    
    /*Mise � jour des flags et du compteur de programme*/
    MAJ_flags_logique(p,p->r[dest]);
    p->r[PC]+=2;
  }  
}


void not( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];  
  unsigned short int source;
  unsigned short int dest;
  
  printf("not\n");
  /*r�cup�ration de la valeur de la source*/
  if(get_operande_source_1(p,ad,mot,&source)){
    /*r�cup�ration du num�ro de registre contenant la source ou de son adresse m�moire*/
    get_operande_dest_1(p,ad,mot,&dest);

    source = ~source;
    
    if(mot.type_source!=0){
      ad->adresse_memoire = dest;

      /*ajout des modifications en m�moire*/
      ecrire_deux_octets(ad,source);
      /*Mise � jour des flags et du compteur de programme */
      MAJ_flags_logique(p,source);
      p->r[PC]+=2;
      
    }
    else{
      /*si la source est un registre*/
      if( dest <8){
	p->r[dest%8] = source;
	/*Mise � jour des flags et du compteur de programme */
	MAJ_flags_logique(p,source);
	p->r[PC]+=2;

      }
    }
  }
}

/*############################################ Fonctions de branchement #############################################*/

void branchement(processeur *p,char flag,adresse *ad){
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  
  
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if((p->r[RE]&flag)){
      p->r[PC]+=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}

void branchement_not(processeur *p,char flag,adresse *ad){
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if((p->r[RE]&flag)==0){
      p->r[PC]+=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}

void bcc_bgt( processeur liste_processeur[][16], adresse *ad){
  /* fonction test�e */
  printf("bcc_bgt\n");
  branchement_not( &liste_processeur[ad->x][ad->y],C,ad);
}

void bcs_blt( processeur liste_processeur[][16], adresse *ad){
  /* fonction test�e */
  printf("bcs_blt\n");
  branchement(&liste_processeur[ad->x][ad->y],C,ad);
}

void beq( processeur liste_processeur[][16], adresse *ad){
  /*fonction test�e*/
  printf("beq\n");
  branchement(&liste_processeur[ad->x][ad->y],Z,ad);
}

void bne( processeur liste_processeur[][16], adresse *ad){
  /* fonction test�e */
  printf("bne\n");
  branchement_not(&liste_processeur[ad->x][ad->y],Z,ad);
}


void ble( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("ble\n");
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){

    if(p->r[RE]&C ||(p->r[RE]&Z)){
      p->r[PC]+=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}


void bge( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("bge\n");
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if(!(p->r[RE]&C) ||(p->r[RE]&Z)){
      p->r[PC]+=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
  /*commande test�e*/
}

void bra( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    p->r[PC]+=source;
  }
  /*commande test�e*/
}


void bsr( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int dest;
  /*commande test�e*/
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("bsr\n");
  /*on r�cup�re la valeur contenue dans le registre, la m�moire ou la valeur imm�diate*/

  if(get_operande_source_1_ctrl_prg(p,ad,mot,&dest)){
    /*on empile PC+1 l'adresse m�moire de la prochaine instruction*/
    p->r[SP]-=2;
    ad->adresse_memoire = p->r[SP];
    ecrire_deux_octets(ad,(p->r[PC]+2)%256);
    /*on r�cup�re la valeur contenue dans le registre, la m�moire ou la valeur imm�diate et on la met dans PC*/
    p->r[PC] += dest;
  }
}



/*################################## Fonctions de saut #####################################################*/


void jump(processeur *p, char flag,adresse *ad){
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];

  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if((p->r[RE]&flag)){
      p->r[PC]=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}


void jump_not(processeur *p, char flag,adresse *ad){
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if(!(p->r[RE]&flag)){
      p->r[PC]=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}



void jcc_jgt(processeur liste_processeur[][16], adresse *ad){
  /*commande test�e*/
  printf("jcc_jgt\n");  
  jump_not( &liste_processeur[ad->x][ad->y],C,ad);
}

void jcs_jlt( processeur liste_processeur[][16], adresse *ad){
  /*commandes test�e*/
  printf("jcs_jlt\n");
  jump(&liste_processeur[ad->x][ad->y],C,ad);
}

void jeq( processeur liste_processeur[][16], adresse *ad){
  /*commande test�e*/
  printf("jeq\n");
  jump(&liste_processeur[ad->x][ad->y],Z,ad);
}

void jne( processeur liste_processeur[][16], adresse *ad){
  /*commande test�e*/
  printf("jne\n");
  jump_not(&liste_processeur[ad->x][ad->y],Z,ad);
}

void jle( processeur liste_processeur[][16], adresse *ad){
  /*commande test�e*/
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("jle\n");
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if((p->r[RE]&C) ||(p->r[RE]&Z) ){
      p->r[PC]=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}

void rien( processeur liste_processeur[][16], adresse *ad){
  printf("rien\n");
}



void jge( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];
  printf("jge\n");
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&source)){
    if(!(p->r[RE]&C) ||(p->r[RE]&Z) ){
      p->r[PC]=source;
    }
    else{
      p->r[PC]+=2;
    }
  }
}

void jmp( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int source;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];  
/*   printf("jmp\n"); */
  /*commande test�e*/
  if(get_operande_source_1_ctrl_prg(&liste_processeur[ad->x][ad->y],ad,mot,&source)){

    liste_processeur[ad->x%16][ad->y%16].r[PC]=source;
     
  }
 
}

void jsr( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];
  unsigned short int dest;
  mot_un_operande mot = *(mot_un_operande *)&p->ram[p->r[PC]%256];  

  printf("jsr\n");
  if(get_operande_source_1_ctrl_prg(p,ad,mot,&dest)){
    /*on empile PC+1 ((p->r[PC]%256)+2)*/
    p->r[SP]-=2;

    ad->adresse_memoire = p->r[SP];
    ecrire_deux_octets(ad,p->r[PC]%256+2);
    /*on r�cup�re la valeur contenue dans le registre, la m�moire ou la valeur imm�diate et on la met dans PC*/
    p->r[PC] = dest;
  }
}

void rte( processeur liste_processeur[][16], adresse *ad){
  processeur *p = &liste_processeur[ad->x][ad->y];

  printf("rte\n");
  if(p->r[SP]<251){
  
    p->r[RE] = (unsigned short int )p->ram[p->r[SP]%256];
    p->r[SP]+=2;
    p->r[PC] = (unsigned short int )p->ram[p->r[SP]%256];
    p->r[SP]+=2;
  }
  else{
    ajouter_liste_interruption (ad, ILLEGAL);
  }
}

