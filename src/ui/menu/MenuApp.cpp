#include "MenuApp.h"
#include <gtk/gtk.h>
#include <glib-object.h>

MenuApp::MenuApp(){
	widget = gtk_label_new("Menu");
}

void MenuApp::show(){
	gtk_widget_show(widget);
}