#include "window.h"
#include "game/Board.h"
#include "menu/MenuApp.h"

#include <gtk/gtk.h>
#include <glib-object.h>


Window::Window(int* argc,char*** argv){
	gtk_init(argc, argv);
	gtkwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkwindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	GtkWidget *vbox;
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	gtk_container_add (GTK_CONTAINER (gtkwindow), vbox);


	Board* board;
	board = new Board();
	gtk_box_pack_start(GTK_BOX(vbox), board->getWidget(), FALSE, FALSE, 3);
	board->show();

	/*MenuApp* menu;
	menu = new MenuApp();
	gtk_box_pack_start(GTK_BOX(vbox), menu->getWidget(), FALSE, FALSE, 3);
	menu->show();
	*/
	gtk_widget_show(vbox);
}

void Window::show(){
	gtk_window_set_position(GTK_WINDOW(gtkwindow), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(gtkwindow), 250, 200);
	gtk_widget_show(gtkwindow);
	gtk_main();
}