#include "window.h"
#include "game/Board.h"
#include "menu/MenuApp.h"

#include <gtk/gtk.h>
#include <glib-object.h>


Window::Window(int* argc,char*** argv){
	gtk_init(argc, argv);
	gtkwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkwindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	GtkWidget *grid;
	grid = gtk_grid_new ();
	gtk_container_add (GTK_CONTAINER (gtkwindow), grid);


	Board* board;
	board = new Board();
	gtk_grid_attach (GTK_GRID (grid), board->getWidget(), 0, 0, 1, 1);
	board->show();

	MenuApp* menu;
	menu = new MenuApp();
	gtk_grid_attach (GTK_GRID (grid), menu->getWidget(), 0, 1, 1, 1);
	menu->show();

	gtk_widget_show(grid);
}

void Window::show(){
	gtk_widget_show(gtkwindow);
	gtk_main();
}