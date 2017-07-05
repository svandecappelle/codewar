#include "MenuApp.h"
#include <iostream>
#include <gtk/gtk.h>
#include <glib-object.h>


static void open (GtkWidget *f) {
    std::cout << "open" << std::endl;
}

MenuApp::MenuApp(){

	widget = gtk_menu_bar_new();

	GtkWidget* file_menu = gtk_menu_new();
	GtkWidget* help_menu = gtk_menu_new();

	GtkWidget* file_item = gtk_menu_item_new_with_label("File");
	GtkWidget* open_item = gtk_menu_item_new_with_label("Open");
	GtkWidget* quit_item = gtk_menu_item_new_with_label("Quit");

	GtkWidget* help_item = gtk_menu_item_new_with_label("Help");
	GtkWidget* about_item = gtk_menu_item_new_with_label("About");


  g_signal_connect(open_item, "activate", G_CALLBACK(open), NULL);

	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_item);

	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);

	gtk_menu_shell_append(GTK_MENU_SHELL(widget), file_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(widget), help_item);


	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);
}

void MenuApp::show(){
	gtk_widget_show_all(widget);
}
