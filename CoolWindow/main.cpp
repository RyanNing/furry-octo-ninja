#include "main.h"
#include "Tmessage.h"
#include <ctime>
#include <cstring>

/* 开始设置时间  这段代码不要动了 */
/* ---------------------------------------------  */

GtkWidget *time_win;

typedef struct
{
    GtkWidget *h;
    GtkWidget *m;
    GtkWidget *d;
}set_time_type;

time_t get_time(GtkWidget *widget,set_time_type *timer)
{
    guint year;
    guint month;
    guint day;
    gtk_calendar_get_date(GTK_CALENDAR(timer->d),&year,&month,&day);

    const gchar *char_hour =gtk_entry_get_text(GTK_ENTRY(timer->h));
    const gchar *char_min = gtk_entry_get_text(GTK_ENTRY(timer->m));

    if ((strlen(char_hour) != 0) && (strlen(char_min) != 0)) {
        int hour;
        if (char_hour[1] != '\0')
            hour = (char_hour[0] - '0') * 10 + char_hour[1] - '0';
        else
            hour = char_hour[0] - '0';
        int min;
        if (char_min[1] != '\0')
            min = (char_min[0] - '0') * 10 + char_min[1] - '0';
        else
            min = char_min[0] - '0';
        month++;
        int week = (day + 2 * month * 3 * (month + 1)/5 + year + year/4 - year/100 + year/400 + 1)  % 7;

        month--;
        time_t t;
        time_t rawtime;
        struct tm * target_time;
        time ( &rawtime );
        target_time = localtime ( &rawtime ); // 其它参数
        target_time->tm_year = year - 1900;
        target_time->tm_mon= month;     // 月 - 1
        target_time->tm_mday = day ;  // 日
        target_time->tm_hour = hour ;   // 时
        target_time->tm_min = min ; // 分
        target_time->tm_sec = 0 ;  // 秒

        const int s[] ={31,28,31,30,31,30,31,31,30,31,30,31};
        int yday;
        for (int i = 0; i < month; i++)
            yday += s[i];
        yday+=day;
        yday--;

        target_time ->tm_yday = yday;
        t = mktime (target_time);
        gtk_widget_destroy(time_win);
        printf("%s",ctime(&t));

        //send the massege
        qjt=t;
        generate_chat_bubble_box(NULL,send_buffer);
        qjt=0;
        return t;
    }

    struct tm * target_time;
}

void setTime(GtkWidget *widget, gpointer *data)
{
    GtkWidget *time_calendar;
    GtkWidget *time_button;
    GtkWidget *cal_vbox;
    GtkWidget *time_mainbox;
    GtkWidget *minute;
    GtkWidget *hour;
    GtkWidget *time_label;
    GtkWidget *time_vbox;
    GtkWidget *time_hbox;
    GtkWidget *sep;
    set_time_type timer;

    // 创建新的窗口
    //gtk_init();
    time_win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(time_win),"Set Time");
    gtk_window_set_resizable (GTK_WINDOW(time_win), false);
    gtk_window_set_position(GTK_WINDOW(time_win),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(time_win),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    time_mainbox = gtk_hbox_new (FALSE,5);
    gtk_container_add(GTK_CONTAINER(time_win),time_mainbox);

    cal_vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(time_mainbox),cal_vbox);
    time_calendar=gtk_calendar_new();
    gtk_box_pack_start(GTK_BOX(cal_vbox),time_calendar,FALSE,FALSE,5);

    sep=gtk_vseparator_new();
    gtk_box_pack_start(GTK_BOX(time_mainbox),sep,FALSE,FALSE,0);

    // 右侧大的垂直盒子
    time_vbox = gtk_vbox_new(FALSE,15);
    gtk_box_pack_start(GTK_BOX(time_mainbox),time_vbox,FALSE,FALSE,5);

    time_hbox=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(time_vbox),time_hbox,FALSE,FALSE,5);

    time_label=gtk_label_new(_T("设置小时(0 - 23):  "));
    gtk_box_pack_start(GTK_BOX(time_hbox),time_label,FALSE,FALSE,5);
    hour=gtk_entry_new();
    gtk_widget_set_size_request(hour,35,25);
    gtk_box_pack_start(GTK_BOX(time_hbox),hour,FALSE,FALSE,0);

    time_hbox=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(time_vbox),time_hbox,FALSE,FALSE,5);

    time_label=gtk_label_new(_T("设置分钟(0 - 59):"));
    gtk_box_pack_start(GTK_BOX(time_hbox),time_label,FALSE,FALSE,5);
    minute=gtk_entry_new();
    gtk_widget_set_size_request(minute,35,25);
    gtk_box_pack_start(GTK_BOX(time_hbox),minute,FALSE,FALSE,5);

    sep=gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(time_vbox),sep,FALSE,FALSE,5);

    time_button = gtk_button_new_with_label(_T("确定"));
    gtk_box_pack_start(GTK_BOX(time_vbox),time_button,FALSE,FALSE,5);
    gtk_widget_set_size_request(time_button,100,40);
    g_signal_connect(G_OBJECT(time_button),"clicked",G_CALLBACK(get_time),&timer);

    timer.h=hour;
    timer.m=minute;
    timer.d =time_calendar;

    gtk_widget_show_all(time_win);
    gtk_main();
}

/* 完成设置时间的窗口 */
/* ---------------------------------------------  */

bool tell_if_we_can_send()
{
    gchar *text_view_char;
    int entry_char;
    GtkTextIter Start,End;

    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(send_buffer),&Start,&End);
    text_view_char = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(send_buffer),&Start,&End,TRUE);
    entry_char = char_to_id(gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(ID_entry_buffer)));
    if(strlen(text_view_char)!=0)
    {
        if(entry_char>=1000&&entry_char<=9999)
            return true;
        else
            return false;
    }
    else
        return false;
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

char* id_to_char (int id) {

    char * p = new char[5];
    for (int i = 3; i >= 0; i--) {
        p[i] = (id % 10) + '0';
        id = id / 10;
    }
    p[4] = '\0';
    return p;
}

int char_to_id (const char * c) {
    int n = (c[0] - '0') * 1000 + (c[1] - '0') * 100 + (c[2] - '0') * 10 + (c[3] - '0');
    return n;
}

void gtk_menu_item_select_ss (GtkWidget *widget) {
    printf("成功删除！\n");
}

int getDisNum() {
    int n = 0;
    for (int i = 1000; i < 10000; i++)
        if (MEM.memMSG[i].size() != 0)
            n++;
        return n;
}

int P[200],B[200000];

int texthas(const char *s,const char *p){
    int sl=strlen(s);
    int pl=strlen(p);
    P[0]=-1;
    int tp=-1;
    for (int i=1;i<pl;++i){
        while (~tp && p[tp+1]!=p[i]) tp=P[tp];
        if (p[tp+1]==p[i]) tp++;
        P[i]=tp;
    }
    tp=-1;
    for (int i=0;i<sl;++i){
        while (~tp && p[tp+1]!=s[i]) tp=P[tp];
        if (p[tp+1]==s[i]) tp++;
        if (tp+1==pl) return i;
    }
    return -1;
}

void clickToSearch(GtkWidget *widget, gpointer *callback_data) {

    const gchar *searchText = _U(gtk_entry_get_text (GTK_ENTRY(callback_data)));
    if (strlen(searchText) > 0) {
        int ind;


        GtkWidget *searchWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title (GTK_WINDOW(searchWindow), _T("搜索结果"));
        gtk_widget_set_size_request(searchWindow,500,500);
        gtk_window_set_resizable (GTK_WINDOW(searchWindow), false);

        GtkWidget *searchTable = gtk_table_new (2,1,false);
        gtk_container_add(GTK_CONTAINER(searchWindow),searchTable);

        char showLabel[100] = "搜索\"";
        strcat(showLabel,(searchText));
        strcat(showLabel,("\"的结果为:"));
        GtkWidget *label = gtk_label_new( _T(showLabel) );
        gtk_table_attach (GTK_TABLE(searchTable), label, 0, 1, 0, 1, (GtkAttachOptions)(0), (GtkAttachOptions)(0),10,10);

        GtkWidget *search_table_scrolled = gtk_scrolled_window_new(NULL,NULL);
        gtk_widget_show(search_table_scrolled);
        gtk_widget_set_size_request(search_table_scrolled,450,430);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(search_table_scrolled),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(search_table_scrolled),GTK_SHADOW_ETCHED_IN);
        gtk_table_attach (GTK_TABLE(searchTable), search_table_scrolled, 0, 1, 1, 2, (GtkAttachOptions)(1), (GtkAttachOptions)(0),10,0);

        GtkWidget *text = gtk_text_view_new();
        gtk_container_add(GTK_CONTAINER(search_table_scrolled),text);
       // gtk_widget_set_size_request(search_table_scrolled,450,450);
        GtkTextBuffer *search_text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
        //gtk_text_buffer_create_tag(search_text_buffer,"blue_fg","foreground","blue",NULL);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text),GTK_WRAP_CHAR);
        gtk_text_view_set_editable(GTK_TEXT_VIEW(text),FALSE);

        GtkTextIter Start,End;


        for (int i=1000;i<=9999;++i){
            for (int j=0;j<MEM.memMSG[i].size();++j){
                if ((~MEM.memMSG[i][j].second) && (~(ind = texthas(MEM.memMSG[i][j].first.msg,(searchText))))){

                    char temp[500]="";
                    strcpy(temp,MEM.memMSG[i][j].first.toShow_2());
                    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(search_text_buffer),&Start,&End);
                    gtk_text_buffer_insert(GTK_TEXT_BUFFER(search_text_buffer),&End,_T("\n"),strlen(_T("\n")));
                    printf("temp:%s\n",temp);
                    gtk_text_buffer_insert(GTK_TEXT_BUFFER(search_text_buffer),&End,_T(temp),strlen(_T(temp)));
                    gtk_text_buffer_insert(GTK_TEXT_BUFFER(search_text_buffer),&End,_T("\n"),strlen(_T("\n")));


                }
            }
        }
        gtk_widget_show_all (searchWindow);
    }
}

void clickForDetail(GtkWidget *widget, gpointer *callback_data) {
    //const char *p =  gtk_button_get_label (GTK_BUTTON(widget));
    //int id = char_to_id(p);
}

void set_ID_entry_editable(void)
{
    gtk_widget_set_sensitive(ID_entry,TRUE);
}

void set_ID_entry_diseditable(void)
{
    gtk_widget_set_sensitive(ID_entry,FALSE);
}

void clear_chat_store(void)
{
    now_id = -1;
    gtk_list_store_clear(GTK_LIST_STORE(chat_store));
    gint byte;
    byte = gtk_entry_buffer_get_bytes(GTK_ENTRY_BUFFER(ID_entry_buffer));
    gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(ID_entry_buffer),0,byte);

    GtkTextIter Start,End;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(send_buffer),&Start,&End);
    gtk_text_buffer_delete(GTK_TEXT_BUFFER(send_buffer),&Start,&End);
}

static gint my_button_handler(GtkWidget *widget,GdkEvent *event)
{
    GtkMenu *menu;
    GdkEventButton *event_button;
    g_return_val_if_fail(widget!=NULL,FALSE);
    g_return_val_if_fail(GTK_IS_MENU(widget),FALSE);
    g_return_val_if_fail(event!=NULL,FALSE);
    menu=GTK_MENU(widget);
    if(event->type==GDK_BUTTON_PRESS)
    {
        event_button=(GdkEventButton *)event;
        if(event_button->button==RIGHT_BUTTON)
        {
            gtk_menu_popup(menu,NULL,NULL,NULL,NULL,event_button->button,event_button->time);
            return TRUE;
        }
    }
    return FALSE;
}

GtkWidget *create_main_window(void)
{
    //GtkWidget *main_window;
    GtkWidget *main_hbox;

    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(main_window);
    gtk_widget_set_size_request(main_window,260+575,550);
    char title[50]="";
    strcat(title,"Mini Chat - ");
    strcat(title,id_to_char(quanjuID));
    gtk_window_set_title (GTK_WINDOW(main_window), _T(title));
    gtk_window_set_resizable(GTK_WINDOW(main_window),FALSE);

    main_hbox = gtk_hbox_new(FALSE,1);
    gtk_widget_show(main_hbox);
    gtk_container_add(GTK_CONTAINER(main_window),main_hbox);

    GtkWidget *djrMainBox = gtk_vbox_new(false,10);
    gtk_widget_show(djrMainBox);
    gtk_box_pack_start(GTK_BOX(main_hbox),djrMainBox,FALSE,FALSE,0);
    gtk_widget_set_size_request(djrMainBox,260,550);

    gtk_container_set_border_width(GTK_CONTAINER(djrMainBox), 10);

    GtkWidget *djrSearchBox = gtk_hbox_new(false, 20);
    gtk_widget_show(djrSearchBox);
    gtk_box_pack_start(GTK_BOX(djrMainBox), djrSearchBox, false, false, 0);


    GtkWidget *entryAlign = gtk_alignment_new (0.5,0.5,0,0);
    GtkWidget *djrEntry = gtk_entry_new_with_max_length(50);
    gtk_widget_set_size_request(djrEntry,170,25);
    gtk_widget_show(entryAlign);
    gtk_widget_show(djrEntry);
    gtk_box_pack_start(GTK_BOX(djrSearchBox), entryAlign, TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (entryAlign), djrEntry);


    GtkWidget *djrButton = gtk_button_new_with_label (_T("搜索"));
    gtk_widget_set_size_request(djrButton,40,25);
    gtk_widget_show(djrButton);
    gtk_box_pack_start(GTK_BOX(djrSearchBox), djrButton, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT(djrButton), "clicked", G_CALLBACK(clickToSearch) , djrEntry);



    GtkWidget *idScroll=gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_show(idScroll);

    gtk_box_pack_start(GTK_BOX(djrMainBox), idScroll, TRUE, TRUE, 0);
    gtk_widget_set_size_request(idScroll,220,420);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(idScroll),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(idScroll),GTK_SHADOW_ETCHED_IN);

        GtkTreeViewColumn *contact_column;
        GtkCellRenderer *contact_renderer;
        GtkTreeSelection *contact_select;

        contact_store = gtk_list_store_new(COLUMN_N_2,GDK_TYPE_PIXBUF,G_TYPE_INT);

        contact_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(contact_store));
        gtk_widget_show(contact_list);
        gtk_container_add(GTK_CONTAINER(idScroll),contact_list);

        contact_select = gtk_tree_view_get_selection(GTK_TREE_VIEW(contact_list));
        gtk_tree_selection_set_mode(contact_select,GTK_SELECTION_SINGLE);
        g_signal_connect(G_OBJECT(contact_select),"changed",G_CALLBACK(clickForDetail),NULL);

        contact_renderer = gtk_cell_renderer_pixbuf_new();
        contact_column = gtk_tree_view_column_new_with_attributes("photo",contact_renderer,"pixbuf",CONTACT_PIC,NULL);
	    gtk_tree_view_append_column(GTK_TREE_VIEW(contact_list),contact_column);

        contact_renderer = gtk_cell_renderer_text_new();
        contact_column = gtk_tree_view_column_new_with_attributes("ID",contact_renderer,"text",CONTACT_ID,NULL);
	    gtk_tree_view_append_column(GTK_TREE_VIEW(contact_list),contact_column);

	    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(contact_list),FALSE);



            delete_contact_menu=GTK_MENU_SHELL(gtk_menu_new());
            GtkWidget *delete_contact_menu_item=gtk_menu_item_new_with_label(_T("删除该联系人所有信息"));
            gtk_menu_shell_append(GTK_MENU_SHELL(delete_contact_menu),delete_contact_menu_item);
            gtk_widget_show(delete_contact_menu_item);

            g_signal_connect(G_OBJECT(contact_select),"changed",G_CALLBACK(switch_contact),contact_select);
            g_signal_connect(GTK_TREE_VIEW(contact_list),"button_press_event",G_CALLBACK(right_click_contact),NULL);
            g_signal_connect(G_OBJECT(delete_contact_menu_item),"activate",G_CALLBACK(delete_contact),contact_select);

    GtkWidget *newBox = gtk_hbox_new(false,5);
    gtk_widget_show(newBox);
    gtk_box_pack_start(GTK_BOX(djrMainBox), newBox, false, false, 0);

    GtkWidget *newMsg = gtk_button_new_with_label ("+");
    GtkWidget *halign = gtk_alignment_new (0.5,1,0.5,0.5);
    gtk_widget_show(halign);
    gtk_widget_show(newMsg);
    gtk_container_add (GTK_CONTAINER (newBox), halign);
    gtk_container_add (GTK_CONTAINER (halign), newMsg);
    g_signal_connect(G_OBJECT(newMsg),"clicked",G_CALLBACK(set_ID_entry_editable),NULL);
    g_signal_connect(G_OBJECT(newMsg),"clicked",G_CALLBACK(clear_chat_store),NULL);




    GtkWidget *outer_table;

    GtkWidget *title_separator;

    GtkWidget *chat_zone;
        GtkTreeViewColumn *column;
        GtkCellRenderer *renderer;
        GtkTreeSelection *select;

    GtkWidget *send_frame;
        GtkWidget *frame_table;
        GtkWidget *text_scrolled;
        GtkWidget *send_button;

    outer_table = gtk_table_new(5,1,FALSE);
    gtk_widget_show(outer_table);
    gtk_box_pack_start(GTK_BOX(main_hbox),outer_table,FALSE,FALSE,0);

    GtkWidget *title_box;
    GtkWidget *title_label1,*title_label2;
    title_box = gtk_hbox_new(FALSE,1);
    gtk_widget_show(title_box);
    gtk_table_attach(GTK_TABLE(outer_table),title_box,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

        title_label1 = gtk_label_new(("To: "));
        gtk_widget_show(title_label1);
        gtk_box_pack_start(GTK_BOX(title_box),title_label1,FALSE,FALSE,0);

        ID_entry = gtk_entry_new_with_max_length(50);
        gtk_widget_show(ID_entry);
        gtk_widget_set_size_request(ID_entry,50,25);
        gtk_box_pack_start(GTK_BOX(title_box),ID_entry,FALSE,FALSE,0);
        gtk_widget_set_sensitive(ID_entry,FALSE);
        ID_entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(ID_entry));

        title_label2 = gtk_label_new((" destination ID"));
        gtk_widget_show(title_label2);
        gtk_box_pack_start(GTK_BOX(title_box),title_label2,FALSE,FALSE,0);


    title_separator = gtk_hseparator_new();
    gtk_widget_show(title_separator);
    gtk_widget_set_size_request(GTK_WIDGET(title_separator),550,0);

    gtk_table_attach(GTK_TABLE(outer_table),title_separator,0,1,1,2,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,1);

    chat_zone = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_show(chat_zone);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(chat_zone),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(chat_zone),GTK_SHADOW_ETCHED_IN);
    gtk_widget_set_size_request(GTK_WIDGET(chat_zone),550,370);

            delete_bubble_menu=GTK_MENU_SHELL(gtk_menu_new());
            GtkWidget *delete_bubble_menu_item=gtk_menu_item_new_with_label(_T("删除"));
            gtk_menu_shell_append(GTK_MENU_SHELL(delete_bubble_menu),delete_bubble_menu_item);
            gtk_widget_show(delete_bubble_menu_item);

        chat_store = gtk_list_store_new(COLUMN_N,GDK_TYPE_PIXBUF,GDK_TYPE_PIXBUF,G_TYPE_INT);

        bubble_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(chat_store));
        gtk_widget_show(bubble_list);
        gtk_container_add(GTK_CONTAINER(chat_zone),bubble_list);

        select = gtk_tree_view_get_selection(GTK_TREE_VIEW(bubble_list));
        gtk_tree_selection_set_mode(select,GTK_SELECTION_SINGLE);
        g_signal_connect(GTK_TREE_VIEW(bubble_list),"button_press_event",G_CALLBACK(right_click_bubble),NULL);
        g_signal_connect(G_OBJECT(delete_bubble_menu_item),"activate",G_CALLBACK(delete_bubble),select);

        renderer = gtk_cell_renderer_pixbuf_new();
        column = gtk_tree_view_column_new_with_attributes("      others' messages                                  ",renderer,"pixbuf",OTHER_MESSAGE,NULL);
	    gtk_tree_view_append_column(GTK_TREE_VIEW(bubble_list),column);

        renderer = gtk_cell_renderer_pixbuf_new();
        column = gtk_tree_view_column_new_with_attributes("                          my messages",renderer,"pixbuf",MY_MESSAGE,NULL);
	    gtk_tree_view_append_column(GTK_TREE_VIEW(bubble_list),column);

        //renderer = gtk_cell_renderer_text_new();
        //column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",MESSAGE_ID,NULL);
	    //gtk_tree_view_append_column(GTK_TREE_VIEW(bubble_list),column);

    gtk_table_attach(GTK_TABLE(outer_table),chat_zone,0,1,2,3,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

    send_frame = gtk_frame_new(NULL);
    gtk_widget_show(send_frame);
    gtk_widget_set_size_request(GTK_WIDGET(send_frame),550,95);

    gtk_table_attach(GTK_TABLE(outer_table),send_frame,0,1,3,4,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,7);

        frame_table = gtk_table_new(1,2,FALSE);
        gtk_widget_show(frame_table);
        gtk_container_add(GTK_CONTAINER(send_frame),frame_table);

        text_scrolled = gtk_scrolled_window_new(NULL,NULL);
        gtk_widget_show(text_scrolled);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(text_scrolled),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(text_scrolled),GTK_SHADOW_ETCHED_IN);
        gtk_widget_set_size_request(GTK_WIDGET(text_scrolled),450,60);
        gtk_table_attach(GTK_TABLE(frame_table),text_scrolled,0,1,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

        send_text = gtk_text_view_new();
        gtk_widget_show(send_text);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(send_text),GTK_WRAP_CHAR);
        gtk_container_add(GTK_CONTAINER(text_scrolled),send_text);
        send_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(send_text));

        GtkWidget *time_right_box;
        time_right_box = gtk_vbox_new(false,0);
        gtk_widget_show(time_right_box);
        gtk_table_attach(GTK_TABLE(frame_table),time_right_box,1,2,0,1,(GtkAttachOptions)(0),(GtkAttachOptions)(0),10,10);

        send_button = gtk_button_new_with_mnemonic(_T("Send"));
        gtk_widget_show(send_button);
        gtk_box_pack_start(GTK_BOX(time_right_box),send_button,FALSE,FALSE,5);

        GtkWidget *set_time_button;
        set_time_button = gtk_button_new_with_label("Set Time");
        gtk_widget_show(set_time_button);
        gtk_box_pack_start(GTK_BOX(time_right_box),set_time_button,FALSE,FALSE,5);

        g_signal_connect(G_OBJECT(set_time_button),"clicked",G_CALLBACK(setTime),NULL);


    g_signal_connect(G_OBJECT(send_button),"clicked",G_CALLBACK(generate_chat_bubble_box),send_buffer);
    g_signal_connect(G_OBJECT(main_window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    return main_window;
}

void generate_chat_bubble_box(GtkWidget *widget,GtkTextBuffer *send_buffer)
{
    time_t t=qjt;
    GtkTreeIter iter;
    GdkPixbuf *message_bubble;

    GtkTextIter Start,End;
    gchar *send_char;

    //if(tell_if_we_can_send())
    {

        gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(send_buffer),&Start,&End);
        send_char = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(send_buffer),&Start,&End,TRUE);
        gtk_text_buffer_delete(GTK_TEXT_BUFFER(send_buffer),&Start,&End);

        gchar all_id[55],*p;
        strcpy(all_id, gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(ID_entry_buffer)));
        p=all_id;
        if (strlen(all_id) > 4) {
                while (*p){
                while (*p==';') p++;
                if (!(*p)) break;
                int ttt=((*p) - '0')*1000+(*(p+1)-'0')*100 + (*(p+2) - '0') * 10 + (*(p + 3) - '0');
                p++;p++;p++;p++;

                gtk_list_store_clear(GTK_LIST_STORE(chat_store));
                data.init(_U(send_char),ttt,t);
                if(contact_exist[ttt]==0){
                generate_contact_person(ttt);
                contact_exist[ttt]=1;
                }
            }
            gint byte;
            byte = gtk_entry_buffer_get_bytes(GTK_ENTRY_BUFFER(ID_entry_buffer));
            gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(ID_entry_buffer),0,byte);
            return;
        }

        now_id = char_to_id(gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(ID_entry_buffer)));

    //message_bubble = draw_bubble1(_U(send_char));

    //bool tflag = contact_exist[now_id];

    //if(tell_if_we_can_send())
    {
        //gtk_list_store_append(chat_store,&iter);
        //gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,NULL,MY_MESSAGE,message_bubble,MESSAGE_ID,9,-1);

        //~send the massege
        //如果有新联系人，将联系人列表更新。
        if(contact_exist[now_id]==0){
            generate_contact_person(now_id);
            contact_exist[now_id]=1;
        }


        data.init(_U(send_char),now_id,t);
    }

    /*GtkTreeIter another_iter;
    if(tflag)
    {
        gtk_list_store_clear(GTK_LIST_STORE(chat_store));

        for(int i=0;i<MEM.memMSG[now_id].size();i++)
        {
            gtk_list_store_append(chat_store,&another_iter);
            if(MEM.memMSG[now_id][i].second == 1)
            {
                message_bubble = draw_bubble1((MEM.memMSG[now_id][i].first.msg));
                gtk_list_store_set(chat_store,&another_iter,OTHER_MESSAGE,NULL,MY_MESSAGE,message_bubble,-1);
                g_object_unref(message_bubble);
            }
            else if(MEM.memMSG[now_id][i].second == 0)
            {
                message_bubble = draw_bubble2((MEM.memMSG[now_id][i].first.msg));
                gtk_list_store_set(chat_store,&another_iter,OTHER_MESSAGE,message_bubble,MY_MESSAGE,NULL,-1);
                g_object_unref(message_bubble);
            }
            else
                ;
        }
    }*/

    //gint rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(chat_store), NULL);

    //GtkTreePath *path = gtk_tree_path_new_from_indices(rows - 1, -1);
    //gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(bubble_list),path,NULL,FALSE,0,0);

	//g_object_unref(message_bubble);
	//gtk_tree_path_free(path);


	set_ID_entry_diseditable();
    }
    qjt=0;
}


gboolean refresh_right(gpointer pointer)
{
    GtkTreeIter iter;
    GdkPixbuf *message_bubble;

    GtkTextIter Start,End;

   //printf("%s\n",output);
    message_bubble = draw_bubble2((output));

    gtk_list_store_append(chat_store,&iter);
    gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,message_bubble,MY_MESSAGE,NULL,MESSAGE_ID,MEM.memMSG[now_id].size()-1,-1);
    gint rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(chat_store), NULL);

    GtkTreePath *path = gtk_tree_path_new_from_indices(rows - 1, -1);
    gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(bubble_list),path,NULL,FALSE,0,0);

	g_object_unref(message_bubble);
	gtk_tree_path_free(path);

	set_ID_entry_diseditable();
	check2=true;
	return FALSE;
}

void refresh_right_2()
{
    GtkTreeIter iter;
    GdkPixbuf *message_bubble;

    GtkTextIter Start,End;

   //printf("%s\n",output);
    message_bubble = draw_bubble1((output2));

    gtk_list_store_append(chat_store,&iter);
    gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,NULL,MY_MESSAGE,message_bubble,MESSAGE_ID,MEM.memMSG[now_id].size()-1,-1);

    gint rows = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(chat_store), NULL);

    GtkTreePath *path = gtk_tree_path_new_from_indices(rows - 1, -1);
    gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(bubble_list),path,NULL,FALSE,0,0);

	g_object_unref(message_bubble);
	gtk_tree_path_free(path);

	set_ID_entry_diseditable();
	check3 = true;
}

void generate_contact_person(int ID)
{
    contact_exist[ID]=1;
    GtkTreeIter iter;
    GdkPixbuf *contact_photo = gdk_pixbuf_new_from_file("resource/contact_photo.png", NULL);

    gtk_list_store_append(contact_store,&iter);
    gtk_list_store_set(contact_store,&iter,CONTACT_PIC,contact_photo,CONTACT_ID,ID,-1);

    g_object_unref(contact_photo);
}

void delete_bubble(GtkWidget * widget, GtkTreeSelection * select)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    int value;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(select), &model, &iter))
    {
        gtk_tree_model_get(model, &iter, MESSAGE_ID, &value, -1);
        gtk_list_store_remove(GTK_LIST_STORE(chat_store), &iter);
        //printf("%d\n",value);
        //printf("NOW ID = %d\n",now_id);
        MEM.memMSG[now_id][value].second = -1;
    }
}

gboolean right_click_bubble(GtkWidget *widget,GdkEventButton *event,gpointer userdata)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreePath *path;
    GtkTreePath *cousor_path;
    GtkTreeViewColumn *col;
    GtkTreeSelection *select;

    gint x,y;
    gint cell_x, cell_y;

    if (event->button == 1)
        return FALSE;
    if (event->button == 2)
        return TRUE;
    if (event->button == 3) {
    if (event->type == GDK_BUTTON_PRESS)
    {
        GdkEventButton *bevent = (GdkEventButton *)event;
        gtk_menu_popup(GTK_MENU(delete_bubble_menu), NULL, NULL, NULL, NULL,bevent->button, bevent->time);

        x = (gint)event->x;
        y = (gint)event->y;

        gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(bubble_list),x, y, &path, &col, &cell_x, &cell_y);
        gtk_widget_grab_focus(bubble_list);
        gtk_tree_view_set_cursor(GTK_TREE_VIEW(bubble_list),path, NULL, FALSE);
        gtk_tree_path_free(path);
        return TRUE;
    }
}

return FALSE;
}

void delete_contact(GtkWidget * widget, GtkTreeSelection * select)
{
    GtkTreeIter iter;
    GtkTreeModel *model;
    int value;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(select), &model, &iter))
    {
        gtk_tree_model_get(model, &iter, CONTACT_ID, &value, -1);
        //gtk_list_store_remove(GTK_LIST_STORE(contact_store), &iter);
        printf("%d\n",value);
    }
    //int temp_ID = char_to_id(gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(ID_entry_buffer)));
    //if(temp_ID == value)
    clear_chat_store();
}

gboolean right_click_contact(GtkWidget *widget,GdkEventButton *event,gpointer userdata)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreePath *path;
    GtkTreePath *cousor_path;
    GtkTreeViewColumn *col;
    GtkTreeSelection *select;

    gint x,y;
    gint cell_x, cell_y;

    if (event->button == 1)
        return FALSE;
    if (event->button == 2)
        return TRUE;
    if (event->button == 3) {
    if (event->type == GDK_BUTTON_PRESS)
    {
        GdkEventButton *bevent = (GdkEventButton *)event;
        gtk_menu_popup(GTK_MENU(delete_contact_menu), NULL, NULL, NULL, NULL,bevent->button, bevent->time);

        x = (gint)event->x;
        y = (gint)event->y;

        gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(contact_list),x, y, &path, &col, &cell_x, &cell_y);
        gtk_widget_grab_focus(contact_list);
        gtk_tree_view_set_cursor(GTK_TREE_VIEW(contact_list),path, NULL, FALSE);
        gtk_tree_path_free(path);
        return TRUE;
    }
}

return FALSE;
}

void switch_contact(GtkWidget *widget,gpointer select)
{
    GtkTreeIter contact_iter;
    GtkTreeModel *model;
    int value;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(select), &model, &contact_iter))
        gtk_tree_model_get(model, &contact_iter, CONTACT_ID, &value, -1);
    now_id = value;

    GdkPixbuf *contact_photo = gdk_pixbuf_new_from_file("resource/contact_photo.png", NULL);

    gtk_list_store_set(contact_store,&contact_iter,CONTACT_PIC,contact_photo,-1);

    g_object_unref(contact_photo);

        gtk_list_store_clear(GTK_LIST_STORE(chat_store));
        gint byte;
        byte = gtk_entry_buffer_get_bytes(GTK_ENTRY_BUFFER(ID_entry_buffer));
        gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER(ID_entry_buffer),0,byte);

        GtkTextIter Start,End;
        gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(send_buffer),&Start,&End);
        gtk_text_buffer_delete(GTK_TEXT_BUFFER(send_buffer),&Start,&End);

    GtkTreeIter iter;
    GdkPixbuf *chat_bubble;

    printf("left_click_ID:%d\n",now_id);

    printf("number:%d\n",MEM.memMSG[now_id].size());
    MEM.memMSG[now_id][0].first.outputMsg();
    for(int i=0;i<MEM.memMSG[now_id].size();i++)
    {
        gtk_list_store_append(chat_store,&iter);
        if(MEM.memMSG[now_id][i].second == 1)
        {
            chat_bubble = draw_bubble1((MEM.memMSG[now_id][i].first.msg));
            gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,NULL,MY_MESSAGE,chat_bubble,MESSAGE_ID,i,-1);
            g_object_unref(chat_bubble);
        }
        else if(MEM.memMSG[now_id][i].second == 0)
        {
            chat_bubble = draw_bubble2((MEM.memMSG[now_id][i].first.msg));
            gtk_list_store_set(chat_store,&iter,OTHER_MESSAGE,chat_bubble,MY_MESSAGE,NULL,MESSAGE_ID,i,-1);
            g_object_unref(chat_bubble);
        }
        else
            ;
    }

    gtk_entry_set_text(GTK_ENTRY(ID_entry),id_to_char(now_id));
    printf("id_to_char_result:%s\n",id_to_char(now_id));
    set_ID_entry_diseditable();
}

int main(){

    for(int i=1000;i<=9999;i++)
        {
            if(MEM.memMSG[i].size())
            {
                contact_exist[i]=1;

                GtkTreeIter iter;
                GdkPixbuf *contact_photo = gdk_pixbuf_new_from_file("resource/contact_photo.png", NULL);

                gtk_list_store_append(contact_store,&iter);
                gtk_list_store_set(contact_store,&iter,CONTACT_PIC,contact_photo,CONTACT_ID,i,-1);

                g_object_unref(contact_photo);
            }
        }

    gtk_widget_show(main_window);
    gtk_widget_show_all(main_window);
    gtk_main();
    wclosed=1;
    return 0;
}
