#include "MenuApp.h"
#include <gtk/gtk.h>
#include <glib-object.h>

MenuApp::MenuApp(){

	widget = gtk_menu_bar_new();

	GtkWidget* file_menu = gtk_menu_new();
	GtkWidget* help_menu = gtk_menu_new();

	GtkWidget* file = gtk_menu_item_new_with_label("File");
	GtkWidget* open = gtk_menu_item_new_with_label("Open");

	GtkWidget* help = gtk_menu_item_new_with_label("Help");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), file_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), help_menu);

	//gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open);
  	gtk_menu_shell_append(GTK_MENU_SHELL(widget), file_menu);
}

void MenuApp::show(){
	gtk_widget_show(widget);
}