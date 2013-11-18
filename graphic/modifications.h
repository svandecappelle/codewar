#ifndef MODIFICATIONS_H
#define MODIFICATIONS_H
#include "definitions.h"
#include "argumentsGraphiques.h"





void ajouter_modification(adresse *ad,  char val);
void appliquer_modifications(processeur  liste_processeur[][TAILLE]);
void  creer_liste(processeur liste_processeur[][16], int argc, char **argv, adresse ad1, adresse ad2, plateauGraphique *p);
int controle_victoire(processeur liste_processeur[][16],short c1, short c2);
void ajouter_liste_interruption(adresse *ad, char type);
void appliquer_interruptions(processeur  liste_processeur[][TAILLE]);
#endif
