#include <math.h>
#include <stdio.h>
#include "../definitions.h"


int get_Flag_C(processeur *p){
  printf("Flag C pour la commande: %d\n",p->r[RE]&C);
  return p->r[RE]&C;
}
int get_Flag_Z(processeur *p){
  printf("Flag Z pour la commande: %d\n",p->r[RE]&Z);
  return p->r[RE]&Z;
}





void MAJ_N_RES15(processeur *p,short int res){
  /*Mise à jour de N*/
  if(!( p->r[RE]&N ) && res&0x8000){
    p->r[RE]+=N;
  }
  else{
    if(p->r[RE]&N && !res&0x8000){
      p->r[RE]-=N;
    }
  }

}


void MAJ_Z(processeur *p, short int res){
  /*Mise à jour de Z*/
  if(res == 0 && (p->r[RE]&Z)!=0){
    p->r[RE]+=Z;
  }
  else{
    if( res !=0 && p->r[RE]&Z){
      p->r[RE]-=Z;
    }
  }
}



void MAJ_N_move(processeur *p, short int res, char typage){
  unsigned short int masque;
  if(typage==3){
    masque = 0xFFFF;
  }
  else{
    if(typage ==2){
      masque = 0xFF00;
    }
    else{
      masque = 0x00FF;
    }
  }

  if((res&masque) == 0){ /*si le res vaut 0*/
    if(!p->r[RE]&Z){ /*si le flag N vaut 0*/
      p->r[RE]+=Z;   
    }
  }
  else{
    if(p->r[RE]&Z){  /*si la valeur est différente de 0 et que le flag N est différent de 0*/
	p->r[RE]-=Z;
    }
  }
}  
  

void MAJ_flags_move(processeur *p, short int res, char typage){
  if(p->r[RE]&C){  /*Si C!=0 on tourne le flag C à 0*/
    p->r[RE]-=C;
  }

  if(typage&0x03||typage&0x02){ /*si le move est un move ou un mohe.h*/
    MAJ_N_RES15(p,res);
  }
  else{
    if(typage&0x01){ /*si le move est un move.l*/
      if(res&0x0080 && !p->r[RE]&N){ /*si le S7 vaut 1 et le flag N 0*/
	p->r[RE] +=N;
      }
      else{
	if(!res&0x0080 && p->r[RE]&N){ /*Si le S7 vaut 0 et la flag N 1*/
	p->r[RE] -=N;
	}
      } 
    }
  }

  MAJ_N_move(p,res,typage);

}   


void MAJ_flags_cmp_sub(processeur *p, short int res){
  MAJ_N_RES15(p,res);  
  MAJ_Z(p,res);

  /*Mise à jour de C*/
  
  if(res<0 && (p->r[RE]&C)==0){
    p->r[RE]+=C;
  }
  else{
    if(res >= 0 && p->r[RE]&C){
      p->r[RE]-=C;
    }
  }
}


void MAJ_flags_ls(processeur *p, short int index,short int res){

  MAJ_N_RES15(p,res);  
  MAJ_Z(p,res);  

  /*mise à jour de C, C = valeur du dernier bit à avoir été décalé*/
  if(res&(short int)(pow(2,index)) && (p->r[RE]&C)==0){
    
    p->r[RE]+=C;
  }
  else{
    if((res&(short int)(pow(2,index)))==0 && p->r[RE]&C){
      p->r[RE]-=C;
    }
  }
}


void MAJ_flags_logique(processeur *p,short int res){
  MAJ_N_RES15(p,res);  
  MAJ_Z(p,res);  

  /*mise à jour de C : C=0*/
  if(p->r[RE]&C){
    p->r[RE]-=C;
  }
}



