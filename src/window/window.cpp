#include <gtk/gtk.h>
#include <glib-object.h>
#include "window.h"


Window::Window(){
	gtk_init(&argc, &argv);
	gtkwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkwindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}

void Window::show(){
	gtk_widget_show(gtkwindow);
	gtk_main();
}

Window::~Window(){

}