#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "../definitions.h"

unsigned short int get_operande_source_0(processeur *p, adresse *ad,mot_move mot, unsigned short int *source);   /* r�cup�re la valeur donn�e par une op�rande pour la commande MOVE */
unsigned short int get_operande_source_1(processeur *p, adresse *ad,mot_un_operande mot, unsigned short int *source);   /* r�cup�re la valeur donn�e par une op�rande pour les commandes � une op�rande */
unsigned short int get_operande_source_2(processeur *p, adresse *ad,mot_deux_operande mot, unsigned short int *source);   /*r�cup�re la valeur donn�e par une op�rande pour les commandes � une op�rande*/
unsigned short int get_operande_source_1_ctrl_prg(processeur *p,adresse *ad,mot_un_operande mot,unsigned short int * source); /*r�cup�re la valeur donn�e par une op�rande pour les commandes � une op�rande*/

unsigned short int get_operande_dest_0(processeur *p,adresse *ad, mot_move mot, unsigned short int *dest);   /* r�cup�re la valeur donn�e par une op�rande pour la commande MOVE */
unsigned short int  get_operande_dest_1(processeur *p, adresse *ad,mot_un_operande mot, unsigned short int *dest);
unsigned short int  get_operande_dest_1_TRAP(processeur *p, adresse *ad,mot_un_operande mot, unsigned short int *dest);  
unsigned short int get_operande_dest_2(processeur *p, adresse *ad,mot_deux_operande mot, unsigned short int *dest);   /*r�cup�re la valeur donn�e par une op�rande pour les commandes � une op�rande*/
void get_adresse(short int mot, adresse *ad); /*d�code le mot envoy� dans la structure adresse*/
#endif
