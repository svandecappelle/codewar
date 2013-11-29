#include "window.h"
#include "game/Board.h"
#include "IsWidget.h"

#include <gtk/gtk.h>
#include <glib-object.h>


Window::Window(int* argc,char*** argv){
	gtk_init(argc, argv);
	gtkwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkwindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	Board board ();
	// todo find a solution for widget encapsulation
	// board->getWidget();
	// gtk_container_add (GTK_CONTAINER (gtkwindow), board.getWidget());
}

void Window::show(){
	gtk_widget_show(gtkwindow);
	gtk_main();
}