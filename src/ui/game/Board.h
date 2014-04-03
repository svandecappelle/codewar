#ifndef BOARD_H
#define BOARD_H

#include "../IsWidget.h"

#include <gtk/gtk.h>
#include <glib-object.h>

class Board: public IsWidget{
	const int BOARD_WIDTH = 16;
	const int BOARD_HEIGHT = 16;

	public:
		Board();
 		void show(void);
} ;

#endif