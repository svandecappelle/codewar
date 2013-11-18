#ifndef ARG_GRAPHIQUES_H
#define ARG_GRAPHIQUES_H

#include "gtk/gtk.h"

typedef struct coordonnes{
  int x;
  int y;
}coordonnees;

typedef struct argument{
  int argc;
  char ** argv;
  GtkBuilder *window;
}argument;

typedef struct demarage{
  coordonnees xy;
  unsigned int couleur;
  gchar *cheminAssembleur;
}demarage;


typedef struct plateauGraphique{
  demarage demarre[2];
  GtkBuilder *plateau;
}plateauGraphique;


#endif
