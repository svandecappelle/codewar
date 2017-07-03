#include "Board.h"
#include <iostream>
#include <gtk/gtk.h>
#include <glib-object.h>

static void select_color(GtkWidget *widget, gpointer data)
{
	std::cout << "Board color selection. " << std::endl;
	/*
	GtkResponseType result;
	GtkColorSelection *colorsel;

	GtkWidget *dialog = gtk_color_selection_dialog_new("Font Color");
	result = gtk_dialog_run(GTK_DIALOG(dialog));

	if (result == GTK_RESPONSE_OK)
	{
		GdkRGBA color;
		GtkWidget *colorSelection;

		colorSelection = gtk_color_selection_dialog_get_color_selection(GTK_COLOR_SELECTION_DIALOG(dialog));

		gtk_color_selection_get_current_rgba(GTK_COLOR_SELECTION(colorSelection), &color);
		// gtk_widget_override_color(GTK_WIDGET(label), GTK_STATE_NORMAL, &color);
	}

	gtk_widget_destroy(dialog);*/
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
			g_signal_connect (proc, "clicked", G_CALLBACK (select_color), NULL);
			//g_signal_connect_swapped (proc, "clicked", G_CALLBACK (gtk_widget_destroy), NULL);
		}
	}
	// std::cout << "Board builded. " << std::endl;
}

void Board::show(){
	gtk_widget_show(widget);
}
