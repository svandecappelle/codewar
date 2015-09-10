#ifndef MENUAPP_H
#define MENUAPP_H

#include "../IsWidget.h"

#include <gtk/gtk.h>
#include <glib-object.h>

class MenuApp: public IsWidget{

	public:
		MenuApp();
 		void show(void);
} ;

#endif