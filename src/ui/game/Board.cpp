#include "Board.h"
#include <iostream>
#include <gtk/gtk.h>
#include <glib-object.h>

static void select_color(GtkColorButton *button, gpointer user_data) {
	GdkRGBA *color = new GdkRGBA();
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), color);
	std::cout << "Board color selection. " << std::endl;
	std::cout << gdk_rgba_to_string(color) << std::endl;
}


Board::Board(){
	widget = gtk_grid_new();

	// std::cout << "Board Build... " << std::endl;

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			// std::cout << "Board Try insert proc... " << std::endl;
			GtkWidget *proc = gtk_color_button_new();
			gtk_widget_show(proc);
			gtk_grid_attach(GTK_GRID(widget), proc, i , j, 1, 1);
			// std::cout << "Board Proc inserted. " << std::endl;
			g_signal_connect (proc, "color-set", G_CALLBACK (select_color), NULL);
		}
	}
	// std::cout << "Board builded. " << std::endl;
}

void Board::show(){
	gtk_widget_show(widget);
}
