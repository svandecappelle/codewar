#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <glib-object.h>

class Window{
public:
	GtkWidget *gtkwindow;
	Window(); // Constructor
 	~Window(){}; // Destructor
 	void show();
};

#endif /* WINDOW_H_ */