#include "Board.h"
#include <gtk/gtk.h>
#include <glib-object.h>

Board::Board(){
	widget = gtk_button_new_with_label("Board");
}

void Board::show(){
	gtk_widget_show(widget);
}