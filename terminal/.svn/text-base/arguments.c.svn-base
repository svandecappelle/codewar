#include <stdio.h>
#include "definitions.h"
#include "typage_operande.h"
#include "modifications.h"
#include "commandes.h"


typedef unsigned short int (*operande)(unsigned short int mot,processeur *p);

operande liste_type_operande_source[] = {
        get_registre_source,
        get_adressage_indirect_predecremente_source,
	get_adressage_indirect_source,
        get_adressage_indirect_post_incremente_source,
        get_valeur_immediate_source,
};

operande liste_type_operande_dest[] = {
        get_registre_dest,
        get_adressage_indirect_predecremente_dest,
        get_adressage_indirect_dest,
        get_adressage_indirect_post_incremente_dest,
};

/*######################### fonctions de récupération de la valeur de la source #############################*/

unsigned short int typage_move(mot_move mot, unsigned short int val){
  if ( mot.l &&mot.h){/*si c'est un move */
    return val;
  }
  else{
    if(mot.h){ /*si c'est un move.h*/
      return val&0xFF00;
    }
  }

  return val&0x00FF;
}

unsigned short int get_operande_source_0(processeur *p,adresse *ad,mot_move mot,unsigned short int *source){ /*récupère la valeur donnée par une opérande pour la commande MOVE*/
  if(mot.type_source&0x0004 ){ /*si la source est une valeur immédiate ou une adresse*/
    if(mot.type_dest== 0x04 || mot.type_dest == 0x05||(!mot.h&&!mot.l) ){
      /*si la destination est une valeur immédiate ou une adresse */
      p->r[PC]+=4;

      interruption (p,ad, ILLEGAL);
      return 0;
    }
    else{
      *source = typage_move(mot,liste_type_operande_source[ mot.type_source   ] ( mot.val,p));
      return 1;
      /*on appelle la liste d'opérande source avec le mot 2 passé en paramètre*/
    }
  }
  else{
    if( mot.type_dest==0x04||(!mot.h&&!mot.l)){
      /*si la destination est une valeur immédiate*/
      /*on passe à l'instruction suivante et on ajoute une interruption à la liste d'interruptions*/
      p->r[PC]+=4;
      ajouter_liste_interruption (ad, ILLEGAL);

      return 0;
    }
    else{
      *source = typage_move(mot,liste_type_operande_source[mot.type_source]( mot.r,p));
      return 1;
      /*on appelle la liste d'opérande source avec le numéro du registre qui sera utilisé en paramètre*/
    }
  }
  
  return 0;
}


unsigned short int get_operande_source_1(processeur *p,adresse *ad,mot_un_operande mot,unsigned short int * source){ /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/
   
  if( (mot.type_source)&0x04){   /*Si ce n'est pas un registre ou adressage par registre*/

    p->r[PC]+=2;
    ajouter_liste_interruption (ad, ILLEGAL);
    return 0;
  }
  else{

    *source = liste_type_operande_source[mot.type_source](mot.val,p);
    return 1;
  }

  return 0;

}

unsigned short int get_operande_source_1_ctrl_prg(processeur *p,adresse *ad,mot_un_operande mot,unsigned short int * source){ /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/
  
  if( (mot.type_source)==0x05){   /*Si c'est une adresse*/
  
    p->r[PC]+=2;
    ajouter_liste_interruption (ad, ILLEGAL);
    return 0;
  }
  else{
  
    *source = liste_type_operande_source[mot.type_source](mot.val,p);
    return 1;
  }
   return 0;
}

unsigned short int  get_operande_source_2(processeur *p, adresse *ad,mot_deux_operande mot, unsigned short int *source){
  /*récupère la valeur donnée par une opérande pour les commandes à deux opérande*/
  if (mot.type_source==0x05){ /* si c'est une adresse @  */
    p->r[PC]+=2;
    ajouter_liste_interruption (ad, ILLEGAL);
    return 0;
  }
  else{
    *source = liste_type_operande_source[mot.type_source](mot.val,p);
    return 1;
  }
  return 0;
}

/*fonctions de récupération de l'index de la destination*/

unsigned short int get_operande_dest_0(processeur *p,adresse *ad, mot_move mot,unsigned short int *dest){ /*récupère la valeur donnée par une opérande pour la commande MOVE*/

  if( mot.type_source&0x04 ){ /*si la source est une valeur immédiate ou une adresse*/
    *dest = liste_type_operande_dest[ mot.type_dest]( mot.r,p);
    return 1;
    /*on appelle la liste d'opérande destination avec le numéro du registre qui sera utilisé en paramètre*/
  }
  else{
    *dest=liste_type_operande_dest[mot.type_dest]( mot.val,p);
    return 1;
    /*on appelle la liste d'opérande destination avec le mot 2 passé en paramètre*/
  }
  return 0;
}






unsigned short int  get_operande_dest_1_TRAP(processeur *p,adresse *ad, mot_un_operande mot,unsigned short int *dest){ /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/
  if( (mot.type_source)==0x05){   /*Si c'est une adresse*/
    p->r[PC]+=2;
    ajouter_liste_interruption (ad, ILLEGAL);
    return 0;
  }
  else{
    *dest = liste_type_operande_dest[mot.type_source](mot.val,p);
    return 1;
  }
}

unsigned short int  get_operande_dest_1(processeur *p, adresse *ad,mot_un_operande mot,unsigned short int *dest){ /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/
   if( (mot.type_source)&0x04){   /*Si ce n'est pas un registre ou adressage par registre*/
    p->r[PC]+=2;
    ajouter_liste_interruption (ad, ILLEGAL);
    return 0;
  }
  else{
    *dest = liste_type_operande_dest[mot.type_source](mot.val,p);
    return 1;
  }
}



unsigned short int  get_operande_dest_2(processeur *p, adresse *ad,mot_deux_operande mot, unsigned short int *dest){ /*récupère la valeur donnée par une opérande pour les commandes à deux opérande*/
  ad++;
  *dest =  liste_type_operande_dest[0](mot.reg_dest,p);
  return 1;
}




/*traitement de l'adresse codée sur 16 bits*/
void get_adresse(short int mot, adresse *ad){ /*décode le mot envoyé dans la structure adresse*/

  if(mot>>12&0x8){                  /*si le mot décodé est une valeur négative*/
    ad->x+= mot >>12&0xFF;          /*on décale de 12 bits et on masque avec OxFF de manière à obtenir une expression du                                        type 1111XXXX*/
  }
  else{
    ad->x+= mot >> 12;              /*Sinon on décale uniquement*/
  }

  if(mot >> 8 &0x08){               /*Si le mot décalé est une valeur négative*/
    ad->y+= mot >>8&0x0F;           /*on décale sur 8 bits, on isole les bits de position Y en masquant*/
    ad->y+= 0xF0;            /*enfin on ajoute F aux 4 bits de poids fort, de manière à obtenir une valeur du type                                       1111YYYY*/
  }
  else{
    ad->y+= mot >>8 &0x0F;          /*Sinon on décale uniquement la valeur sur 8 bits en la masquant*/
  }
  ad->x = ad->x%16;
  ad->y = ad->y%16;
  ad->adresse_memoire+= mot&0x00FF; /*On isole les bits d'adresse en masquant les 8 bits de poids faible*/
}
