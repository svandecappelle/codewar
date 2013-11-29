#ifndef ISWIDGET_H
#define ISWIDGET_H

#include <gtk/gtk.h>

class IsWidget{
	protected:
		GtkWidget* widget;
	public:
    	GtkWidget* getWidget(void);
};

#endif