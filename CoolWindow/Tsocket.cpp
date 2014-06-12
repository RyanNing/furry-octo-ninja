#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "Tsocket.h"
#include "Tmemory.h"

Tsocket::~Tsocket(){
    closesocket(sockClient);
    MSGsend(Tmessage(ID,0));
    WSACleanup();
}

DWORD WINAPI Tsocket::pf(LPVOID p){
    extern char output[600];
    extern Tmemory MEM;
    //extern gboolean receiveChat(gpointer wbus);
    Tmessage recvMSG;
    SOCKET sockClient=*((SOCKET *)p);
    char recvBuf[nBuf];
    extern bool check;
    extern void generate_contact_person(int ID);
    extern gboolean refresh_right(gpointer pointer);
    extern int now_id;
    extern bool contact_exist[10000];
    extern GtkWidget *contact_list;
    extern GtkListStore *contact_store;
    extern bool check2;
    extern char output[600];
    extern int wclosed;

    while (1){
        recv(sockClient,recvBuf,nBuf,0);
        recvMSG.makeMessage(recvBuf);
        output[0]=0;
        //sprintf(output,"NEW MESSEGE:\n");
        //recvMSG.outputMsg();
        strcpy(output,recvMSG.toShow());
        int tID=recvMSG.selfID;
        if (wclosed) return 0;
        MEM.add(recvMSG,RECV);
        if (tID==now_id){
            check2=false;
            g_idle_add(refresh_right,NULL);
            while (!check2) _sleep(10);
        }
        else{
            if (!contact_exist[tID]){
                generate_contact_person(tID);
            }
            printf("test\n");
            GdkPixbuf *temp_picture = gdk_pixbuf_new_from_file("resource/contact_photo2.png", NULL);
            GtkTreeIter iter;//定义一个迭代器
            GtkTreeModel *pmodel;
            int temp;
            pmodel=gtk_tree_view_get_model(GTK_TREE_VIEW(contact_list));//得到TREEVIEW的model
            gtk_tree_model_get_iter_first(pmodel,&iter);//迭代器定位到第一行
            int columns=gtk_tree_model_get_n_columns(pmodel);//获取行数

            do//开始遍历内容
            {
                gtk_tree_model_get (GTK_TREE_MODEL(pmodel),&iter,1,&temp,-1);
                if(temp==tID)
                {
                    gtk_list_store_set(GTK_LIST_STORE(contact_store),&iter,0,temp_picture,-1);
                    break;
                }
            }while(gtk_tree_model_iter_next(pmodel,&iter));

            g_object_unref(temp_picture);
        }
        //puts(output);
        //check=false;
        //g_idle_add(receive_chat,NULL);
        //while (!check) Sleep(10);
    }
}

Tsocket::Tsocket(){
    extern int quanjuID;
    ID=quanjuID;
    //ID=myID;

    WSAStartup(MAKEWORD(1,1),&wsaData);
    sockClient=socket(AF_INET,SOCK_STREAM,0);
    addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(1234);
    connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

    char sendBuf[nBuf]="";
    sprintf(sendBuf,"%d",ID);
    //puts(sendBuf);
    send(sockClient,sendBuf,nBuf,0);
    CreateThread(NULL,0,pf,(void *)&sockClient,0,NULL);
}

void Tsocket::MSGsend(Tmessage sendMSG){
    sockClient2=socket(AF_INET,SOCK_STREAM,0);
    connect(sockClient2,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
    char sendBuf[nBuf]="";
    sprintf(sendBuf,"%d",ID);
    //puts(sendBuf);
    send(sockClient2,sendBuf,nBuf,0);
    send(sockClient2,sendMSG.toChar(),nBuf,0);
    closesocket(sockClient2);
}
