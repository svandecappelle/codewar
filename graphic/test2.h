#ifndef TEST2_H
#define TEST2_H
#include "argumentsGraphiques.h"

  
argument *argmt;
GtkBuilder *p_builder;
void couleur(GtkColorButton *button, demarage d[]);
void file_changed(GtkButton *button, demarage *d);
void coord_changed(GtkButton *button, demarage *d);
int Demarer(GtkWidget *widget,plateauGraphique *p);
void NewGame(argument *arg);
#endif
