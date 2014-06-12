#pragma once
#pragma comment(lib,"ws2_32")
#pragma comment(lib,"Iphlpapi")
#define nBuf 200
#include <windows.h>
#include "Tmessage.h"
#include "Iphlpapi.h"
#include <Winsock2.h>

class Tsocket{
private:
    WSADATA wsaData;
    SOCKADDR_IN addrSrv;
    SOCKET sockClient,sockClient2;
public:
    int ID;
    Tsocket();
    ~Tsocket();
    int getID();
    static DWORD WINAPI pf(LPVOID p);
    void MSGsend(Tmessage sendMSG);
};
