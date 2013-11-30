#ifndef ISWIDGET_H
#define ISWIDGET_H

#include <gtk/gtk.h>

class IsWidget{
	protected:
		
	public:
		GtkWidget* widget;
    	GtkWidget* getWidget(void);
};

#endif