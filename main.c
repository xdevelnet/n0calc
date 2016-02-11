#include <gtk/gtk.h>
//#include <stdlib.h>
#include <string.h>

static gboolean key_event(GtkWidget *widget, GdkEventKey *event, gpointer data) {
	g_printerr("%s\n", gdk_keyval_name (event->keyval));
	return TRUE;
}

static void dummy () {
}

static void show_content (GtkWidget *widget, gpointer data) {
	GtkTextIter start_iter, end_iter;
	gtk_text_buffer_get_start_iter (data, &start_iter);
	gtk_text_buffer_get_end_iter (data, &end_iter);
	g_printerr("%s\n",gtk_text_buffer_get_text(data, &start_iter, &end_iter, 0));
}

static void show_content2 (GtkWidget *widget, gpointer data) {
	//that will NOT work. Coz we're using text view, not text entry
	g_printerr("%s", gtk_editable_get_chars(data, 0, -1));
}

GtkWidget *place_and_bind_button (const gchar *btn_label, void (*handler), gpointer handled_object, GtkWidget *placer, gint left, gint top, gint width, gint height) {
	GtkWidget *btn_ptr = gtk_button_new_with_label(btn_label);
	g_signal_connect (btn_ptr, "clicked", G_CALLBACK (handler), handled_object);
	gtk_grid_attach(GTK_GRID(placer), btn_ptr, left, top, width, height);
	return btn_ptr;
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "N00b calc");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//gtk_window_set_default_size(GTK_WINDOW(window), 550, 300); useless if u're using set resizable

	gtk_container_set_border_width (GTK_CONTAINER (window), 3);

	GtkWidget *grid = gtk_grid_new ();
	gtk_container_add (GTK_CONTAINER (window), grid);

	GtkWidget *scrolled = gtk_scrolled_window_new (NULL, NULL);
	gtk_widget_set_hexpand (scrolled, TRUE);
	gtk_widget_set_vexpand (scrolled, TRUE);
	gtk_grid_attach(GTK_GRID(grid), scrolled, 0, 0, 4, 1);
	gtk_widget_set_size_request(scrolled, 300, 50);
	gtk_scrolled_window_set_policy((GtkScrolledWindow*) scrolled, GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_visible(gtk_scrolled_window_get_hscrollbar((GtkScrolledWindow*)scrolled), FALSE);

	GtkWidget *textview = gtk_text_view_new (); //I am freaking n00b. I should use gtk_entry_new_with_buffer() instead. KEK!
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));
	gtk_text_buffer_set_text (buffer, "0", -1);

	PangoFontDescription *fnt_desc = pango_font_description_from_string("Tahoma 16");
	gtk_widget_modify_font (textview, fnt_desc);
	pango_font_description_free(fnt_desc);

	gtk_text_view_set_justification(GTK_TEXT_VIEW(textview), GTK_JUSTIFY_RIGHT);
	gtk_widget_set_margin_bottom(textview, 5);
	gtk_widget_set_margin_left(textview, 5);
	gtk_widget_set_margin_right(textview, 5);
	gtk_widget_set_margin_top(textview, 5);
	gtk_container_add(GTK_CONTAINER(scrolled), textview);

	GtkWidget *button = gtk_button_new_with_label ("Quit");
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	g_signal_connect(window, "key-release-event", G_CALLBACK(key_event), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

	place_and_bind_button("info", show_content, buffer, grid, 1, 1, 1, 1);
	place_and_bind_button("AC", dummy, NULL, grid, 2, 1, 1, 1);
	place_and_bind_button("/", dummy, NULL, grid, 3, 1, 1, 1);
	place_and_bind_button("7", dummy, NULL, grid, 0, 2, 1, 1);
	place_and_bind_button("8", dummy, NULL, grid, 1, 2, 1, 1);
	place_and_bind_button("9", dummy, NULL, grid, 2, 2, 1, 1);
	place_and_bind_button("×", dummy, NULL, grid, 3, 2, 1, 1);
	place_and_bind_button("4", dummy, NULL, grid, 0, 3, 1, 1);
	place_and_bind_button("5", dummy, NULL, grid, 1, 3, 1, 1);
	place_and_bind_button("6", dummy, NULL, grid, 2, 3, 1, 1);
	place_and_bind_button("-", dummy, NULL, grid, 3, 3, 1, 1);
	place_and_bind_button("1", dummy, NULL, grid, 0, 4, 1, 1);
	place_and_bind_button("2", dummy, NULL, grid, 1, 4, 1, 1);
	place_and_bind_button("3", dummy, NULL, grid, 2, 4, 1, 1);
	place_and_bind_button("+", dummy, NULL, grid, 3, 4, 1, 2);
	place_and_bind_button("0", dummy, NULL, grid, 0, 5, 1, 1);
	place_and_bind_button(".", dummy, NULL, grid, 1, 5, 1, 1);
	place_and_bind_button("=", dummy, NULL, grid, 2, 5, 1, 1);
	gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
	GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
