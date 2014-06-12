#include "main.h"

void int_ID_to_char_label(int ID,char *label)
{
    int i = 0;
    strcat(label,"To:");
    for(i=6;i>=3;i--)
    {
        label[i] = ID % 10 + '0';
        ID /= 10;
    }
    strcat(label," destination ID");
}

gboolean drag_window(GtkWidget *window,GdkEventButton *event,GdkWindowEdge edge)
{
    if(event->type == GDK_BUTTON_PRESS)
    {
        if(event->button == 1)
        {
            gtk_window_begin_move_drag(GTK_WINDOW(gtk_widget_get_toplevel(window)),event->button,event->x_root,event->y_root,event->time);
        }
    }

    return FALSE;
}

GtkWidget *create_main_window(void)
{
    GtkWidget *main_window;
    GtkWidget *goto_chat_button;

    //GdkPixbuf *main_background = NULL;
    //GdkPixmap *tempPixmap = NULL;
    //GdkBitmap *tempBitmap = NULL;

    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(main_window,320,570);
    gtk_window_set_resizable(GTK_WINDOW(main_window),FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(main_window),FALSE);

    //gtk_widget_set_app_paintable(main_window,TRUE);
    //gtk_widget_realize(main_window);

    //main_background = gdk_pixbuf_new_from_file("resource/main_window.png",NULL);
    //gdk_pixbuf_render_pixmap_and_mask(main_background,&tempPixmap,&tempBitmap,128);
    //gtk_widget_shape_combine_mask(main_window,tempBitmap,0,0);
    //gdk_window_set_back_pixmap(main_window->window,tempPixmap,FALSE);

    //g_object_unref(main_background);
    //g_object_unref(tempBitmap);
    //g_object_unref(tempPixmap);

    goto_chat_button = gtk_button_new_with_mnemonic("打开聊天窗口");
    gtk_widget_show(goto_chat_button);
    gtk_container_add(GTK_CONTAINER(main_window),goto_chat_button);

    g_signal_connect(G_OBJECT(main_window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    //g_signal_connect(G_OBJECT(main_window),"button_press_event",G_CALLBACK(drag_window),NULL);
    destination_ID = 1009;
    g_signal_connect(G_OBJECT(goto_chat_button),"button_press_event",G_CALLBACK(generate_chat_window),NULL);

    //gtk_widget_add_events(GTK_WIDGET(main_window),GDK_POINTER_MOTION_HINT_MASK);
    //gtk_widget_add_events(GTK_WIDGET(main_window),GDK_BUTTON_PRESS_MASK);

    return main_window;
}

GtkWidget *create_chat_window(void)
{
    GtkWidget *chat_window;
    GtkWidget *outer_table;

    GtkWidget *title_label;

    GtkWidget *title_separator;

    GtkWidget *chat_zone;

        GtkTreeViewColumn *column;
        GtkCellRenderer *renderer;
        GtkTreeSelection *select;

    GtkWidget *send_frame;
        GtkWidget *frame_table;
        GtkWidget *text_scrolled;
        GtkWidget *send_text;
        GtkWidget *send_button;

    //GdkPixbuf *chat_background = NULL;
    //GdkPixmap *tempPixmap = NULL;
    //GdkBitmap *tempBitmap = NULL;

    chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(chat_window,575,550);
    gtk_window_set_resizable(GTK_WINDOW(chat_window),FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(chat_window),FALSE);

    //gtk_widget_set_app_paintable(chat_window,TRUE);
    //gtk_widget_realize(chat_window);

    //chat_background = gdk_pixbuf_new_from_file("resource/main_window.png",NULL);
    //gdk_pixbuf_render_pixmap_and_mask(chat_background,&tempPixmap,&tempBitmap,128);
    //gtk_widget_shape_combine_mask(chat_window,tempBitmap,0,0);
    //gdk_window_set_back_pixmap(chat_window->window,tempPixmap,FALSE);

    outer_table = gtk_table_new(4,1,FALSE);
    gtk_widget_show(outer_table);
    gtk_container_add(GTK_CONTAINER(chat_window),outer_table);

    char label[ENOUGH_LABEL] = "";
    int_ID_to_char_label(destination_ID,label);
    title_label = gtk_label_new(label);
    gtk_widget_show(title_label);

    gtk_table_attach(GTK_TABLE(outer_table),title_label,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

    title_separator = gtk_hseparator_new();
    gtk_widget_show(title_separator);
    gtk_widget_set_size_request(GTK_WIDGET(title_separator),550,0);

    gtk_table_attach(GTK_TABLE(outer_table),title_separator,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

    chat_zone = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_show(chat_zone);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(chat_zone),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(chat_zone),GTK_SHADOW_ETCHED_IN);
    gtk_widget_set_size_request(GTK_WIDGET(chat_zone),550,370);

        chat_store = gtk_list_store_new(COLUMN_N,GDK_TYPE_PIXBUF,GDK_TYPE_PIXBUF,G_TYPE_STRING);

        bubble_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(chat_store));
        gtk_widget_show(bubble_list);
        gtk_container_add(GTK_CONTAINER(chat_zone),bubble_list);

        select = gtk_tree_view_get_selection(GTK_TREE_VIEW(bubble_list));
        gtk_tree_selection_set_mode(select,GTK_SELECTION_SINGLE);
        g_signal_connect(G_OBJECT(select),"changed",G_CALLBACK(delete_bubble),NULL);

        renderer = gtk_cell_renderer_pixbuf_new();
        column = gtk_tree_view_column_new_with_attributes("      others' messages                                  ",renderer,"pixbuf",OTHER_MESSAGE,NULL);
	    gtk_tree_view_append_column(GTK_TREE_VIEW(bubble_list),column);

        renderer = gtk_cell_renderer_pixbuf_new();
        column = gtk_tree_view_column_new_with_attributes("                          my messages",renderer,"pixbuf",MY_MESSAGE,NULL);
	    gtk_tree_view_append_column(GTK_TREE_VIEW(bubble_list),column);

	    //gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(bubble_list),FALSE);

    gtk_table_attach(GTK_TABLE(outer_table),chat_zone,0,1,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

    send_frame = gtk_frame_new(NULL);
    gtk_widget_show(send_frame);
    gtk_widget_set_size_request(GTK_WIDGET(send_frame),550,85);

    gtk_table_attach(GTK_TABLE(outer_table),send_frame,0,1,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

        frame_table = gtk_table_new(1,2,FALSE);
        gtk_widget_show(frame_table);
        gtk_container_add(GTK_CONTAINER(send_frame),frame_table);

        text_scrolled = gtk_scrolled_window_new(NULL,NULL);
        gtk_widget_show(text_scrolled);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(text_scrolled),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(text_scrolled),GTK_SHADOW_ETCHED_IN);
        gtk_widget_set_size_request(GTK_WIDGET(text_scrolled),470,60);
        gtk_table_attach(GTK_TABLE(frame_table),text_scrolled,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

        send_text = gtk_text_view_new();
        gtk_widget_show(send_text);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(send_text),GTK_WRAP_CHAR);
        gtk_container_add(GTK_CONTAINER(text_scrolled),send_text);

        send_button = gtk_button_new_with_mnemonic("send");
        gtk_widget_show(send_button);
        gtk_table_attach(GTK_TABLE(frame_table),send_button,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);
        GTK_WIDGET_SET_FLAGS(send_button,GTK_CAN_DEFAULT);
        gtk_widget_grab_default(send_button);

    //g_object_unref(chat_background);
    //g_object_unref(tempBitmap);
    //g_object_unref(tempPixmap);

    g_signal_connect(G_OBJECT(chat_window),"destroy",G_CALLBACK(gtk_widget_destroy),chat_window);
    whos_message_flag = 1;
    g_signal_connect(G_OBJECT(send_button),"clicked",G_CALLBACK(generate_chat_bubble_box),NULL);
    //g_signal_connect(G_OBJECT(chat_window),"button_press_event",G_CALLBACK(drag_window),NULL);

    //gtk_widget_add_events(GTK_WIDGET(chat_window),GDK_POINTER_MOTION_HINT_MASK);
    //gtk_widget_add_events(GTK_WIDGET(chat_window),GDK_BUTTON_PRESS_MASK);

    return chat_window;
}

void generate_chat_window(void)
{
    GtkWidget *chat_window;

    chat_window = create_chat_window();
    gtk_widget_show(chat_window);
}

void generate_chat_bubble_box(void)
{
    whos_message_flag ++;

    GtkTreeIter iter;
    GdkPixbuf *message_bubble;

    if(whos_message_flag %2 != 0)
        message_bubble = draw_bubble1(_U("你sadasdsadasddsa是我知道heyhey黑喂狗！//////（tangqiang）"));
    else
        message_bubble = draw_bubble2(_U("mihuo迷惑万千，雨过天晴"));

    gtk_list_store_append(chat_store,&iter);
    if(whos_message_flag % 2 == 0)
	    gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,NULL,MY_MESSAGE,message_bubble,-1);
	else
        gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,message_bubble,MY_MESSAGE,NULL,-1);


    gint rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(chat_store), NULL);

    GtkTreePath *path = gtk_tree_path_new_from_indices(rows - 1, -1);
    gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(bubble_list),path,NULL,FALSE,0,0);

	g_object_unref(message_bubble);
}

void delete_bubble(void){}

int main(int argc,char *argv[])
{
    GtkWidget *main_window;

    gtk_init(&argc,&argv);

    main_window = create_main_window();
    gtk_widget_show(main_window);

    gtk_main();

    return 0;
}
