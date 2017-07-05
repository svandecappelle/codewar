#include "window.h"
#include "game/Board.h"
#include "menu/MenuApp.h"

#include <gtk/gtk.h>
#include <glib-object.h>


Window::Window(int* argc,char*** argv){
	gtk_init(argc, argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	GtkWidget *vbox;
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	MenuApp* menu;
	menu = new MenuApp();
	gtk_box_pack_start(GTK_BOX(vbox), menu->getWidget(), FALSE, FALSE, 0);
	menu->show();

	Board* board;
	board = new Board();
	gtk_box_pack_start(GTK_BOX(vbox), board->getWidget(), FALSE, FALSE, 1);
	board->show();

	gtk_widget_show_all(vbox);
}

void Window::show(){
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
	gtk_widget_show(window);
	gtk_main();
}
