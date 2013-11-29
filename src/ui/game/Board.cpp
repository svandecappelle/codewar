#include "Board.h"
#include <gtk/gtk.h>
#include <glib-object.h>

Board::Board(){
	widget = gtk_label_new("GTK_WINDOW_TOPLEVEL");
}

void Board::show(){
	gtk_widget_show(widget);
}