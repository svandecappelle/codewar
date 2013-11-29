#ifndef BOARD_H
#define BOARD_H

#include "../IsWidget.h"

#include <gtk/gtk.h>
#include <glib-object.h>

class Board: public IsWidget{
	
	public:
		Board();
 		void show(void);
} ;

#endif