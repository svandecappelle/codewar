#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H
/*interpreteur.h*/
#include "definitions.h"
#include "commandes.h"
#include "argumentsGraphiques.h"
#include "gtk/gtk.h"
/*Fonction retournant l'�criture correspondant � l'execution du mot binaire trouv� � l'adresse pc du processeur pass� en param�tre*/

void jeu( processeur liste_processeur[][16],int nbTours,plateauGraphique *plateau);
#endif
