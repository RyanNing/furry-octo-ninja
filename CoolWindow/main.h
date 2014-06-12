#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <gtk/gtk.h>
#include <string.h>
#include <vector>
#include <ctype.h>

using namespace std;

#include "textCodeConvert.h"
#include "drawBubble.h"
#include "Send.h"
#include "Tmemory.h"
#include "Tmessage.h"
#include "Tsocket.h"

#define RECV 0
#define SEND 1
#define RIGHT_BUTTON 3

GtkWidget *create_main_window(void);
GtkWidget *create_chat_window(void);
void generate_chat_bubble_box(GtkWidget *widget,GtkTextBuffer *send_buffer);
void generate_contact_person(int ID);
void set_ID_entry_editable(void);
void set_ID_entry_diseditable(void);
void delete_bubble(GtkWidget * widget, GtkTreeSelection * select);
void delete_contact(GtkWidget * widget, GtkTreeSelection * select);
gboolean drag_window(GtkWidget *window,GdkEventButton *event,GdkWindowEdge edge);
gboolean right_click_bubble(GtkWidget *widget,GdkEventButton *event,gpointer userdata);
gboolean right_click_contact(GtkWidget *widget,GdkEventButton *event,gpointer userdata);

gboolean refresh_right(gpointer pointer);
void switch_contact(GtkWidget *widget,gpointer select);

bool tell_if_we_can_send();

int destination_ID = 1000;

GtkWidget *main_window;
    GtkWidget *ID_entry;
    GtkEntryBuffer *ID_entry_buffer;

GtkListStore *chat_store = NULL;
    GtkWidget *bubble_list;

GtkListStore *contact_store = NULL;
    GtkWidget *contact_list;

GtkListStore *search_result_store = NULL;
    GtkWidget *search_list;

GtkWidget *send_text;
GtkTextBuffer *send_buffer;

GtkMenuShell *delete_bubble_menu;
GtkMenuShell *delete_contact_menu;

enum
{
    OTHER_MESSAGE,
    MY_MESSAGE,
    MESSAGE_ID,
    COLUMN_N
};

enum
{
    CONTACT_PIC,
    CONTACT_ID,
    COLUMN_N_2
};

char* id_to_char (int id);
int char_to_id (const char * c);
void gtk_menu_item_select_ss (GtkWidget *widget);
void clickToSearch(GtkWidget *widget, gpointer *callback_data);
void clickForDetail(GtkWidget *widget, gpointer *callback_data);
static gint my_button_handler(GtkWidget *widget,GdkEvent *event);

/*
int getID(){
    u_char g_ucLocalMac[6];
    ZeroMemory(g_ucLocalMac,6);
    PIP_ADAPTER_INFO pAdapterInfo=NULL;
    ULONG ulLen=0;
    ::GetAdaptersInfo(pAdapterInfo,&ulLen);
    pAdapterInfo=(PIP_ADAPTER_INFO)::GlobalAlloc(GPTR,ulLen);
    if(::GetAdaptersInfo(pAdapterInfo,&ulLen)== ERROR_SUCCESS){
		if(pAdapterInfo!= NULL){
			memcpy(g_ucLocalMac,pAdapterInfo->Address,6);
		}
	}
	u_char *p=g_ucLocalMac;
    long long hash=0;
    for (int i=0;i<6;++i){
        hash<<=8;
        hash+=p[i];
    }
    hash%=8997;
    hash+=1000;
    return hash;
}
*/

int quanjuID;

int getID(){
    int ret=0;
    while (1){
        printf("INPUT ID (1000-9999):\n");
        scanf("%d",&ret);getchar();
        if (ret>=1000 && ret<=9999)
        return ret;
    }
}

int now_id;
bool check2;

//GtkWidget *main_window;
int wclosed;

class draw_windows{
public:
    draw_windows(){
        //memset(contact_exist,0,sizeof(contact_exist));
        wclosed=0;
        quanjuID=getID();
        now_id = -1;
        int argc=0;
        char **argv=NULL;
        gtk_init(&argc,&argv);
        create_main_window();
    }
} WIND;
char output[600]="";
char output2[600]="";
bool check;
bool check3;
bool contact_exist[10000];
time_t qjt;

Tmemory MEM;
Tsocket CONN;
Send data;

#endif // MAIN_H_INCLUDED
