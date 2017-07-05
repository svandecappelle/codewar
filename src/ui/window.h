#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>
#include <glib-object.h>

class Window{
	GtkWidget *window;

	public:
 		void show(void);
 		Window (int* argc, char*** argv);
} ;

#endif /* WINDOW_H_ */
