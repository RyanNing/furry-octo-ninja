#ifndef DISABLEWINDOWS_H_INCLUDED
#define DISABLEWINDOWS_H_INCLUDED

void disable_window(GtkWidget *widget,gpointer pointer)
{
    gtk_widget_set_sensitive(GTK_WIDGET(pointer),FALSE);
}

#endif // DISABLEWINDOWS_H_INCLUDED
