#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "../definitions.h"

unsigned short int get_operande_source_0(processeur *p, adresse *ad,mot_move mot, unsigned short int *source);   /* récupère la valeur donnée par une opérande pour la commande MOVE */
unsigned short int get_operande_source_1(processeur *p, adresse *ad,mot_un_operande mot, unsigned short int *source);   /* récupère la valeur donnée par une opérande pour les commandes à une opérande */
unsigned short int get_operande_source_2(processeur *p, adresse *ad,mot_deux_operande mot, unsigned short int *source);   /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/
unsigned short int get_operande_source_1_ctrl_prg(processeur *p,adresse *ad,mot_un_operande mot,unsigned short int * source); /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/

unsigned short int get_operande_dest_0(processeur *p,adresse *ad, mot_move mot, unsigned short int *dest);   /* récupère la valeur donnée par une opérande pour la commande MOVE */
unsigned short int  get_operande_dest_1(processeur *p, adresse *ad,mot_un_operande mot, unsigned short int *dest);
unsigned short int  get_operande_dest_1_TRAP(processeur *p, adresse *ad,mot_un_operande mot, unsigned short int *dest);  
unsigned short int get_operande_dest_2(processeur *p, adresse *ad,mot_deux_operande mot, unsigned short int *dest);   /*récupère la valeur donnée par une opérande pour les commandes à une opérande*/
void get_adresse(short int mot, adresse *ad); /*décode le mot envoyé dans la structure adresse*/
#endif
