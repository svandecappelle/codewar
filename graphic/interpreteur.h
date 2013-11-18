#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H
/*interpreteur.h*/
#include "definitions.h"
#include "commandes.h"
#include "argumentsGraphiques.h"
#include "gtk/gtk.h"
/*Fonction retournant l'écriture correspondant à l'execution du mot binaire trouvé à l'adresse pc du processeur passé en paramètre*/

void jeu( processeur liste_processeur[][16],int nbTours,plateauGraphique *plateau);
#endif
