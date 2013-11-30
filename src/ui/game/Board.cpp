#include "Board.h"
#include <gtk/gtk.h>
#include <glib-object.h>

Board::Board(){
	widget = gtk_label_new("Board");
}

void Board::show(){
	gtk_widget_show(widget);
}