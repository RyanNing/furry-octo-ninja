#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#include "Tmemory.h"

using namespace std;

Tmemory::Tmemory(){
    extern int quanjuID;
    int iptID=quanjuID;
    ID=iptID;
    fileName[0]=0;
    sprintf(fileName,"%d.sms",ID);
    readFile();
}

Tmemory::~Tmemory(){
    writeFile();
}

void Tmemory::writeFile(){
    FILE *fp=fopen(fileName,"w");
    for (int i=1000;i<=9999;++i){
        for (int j=0;j<memMSG[i].size();++j){
            memMSG[i][j].first.outputMsg();
            printf("[UP]This message's flag = %d\n",memMSG[i][j].second);
            if (memMSG[i][j].second==-1) continue;
            fwrite(memMSG[i][j].first.toChar(),159,1,fp);
            fprintf(fp," %d\n",memMSG[i][j].second);
        }
    }
    fclose(fp);
}

void Tmemory::readFile(){
    for (int i=1000;i<=9999;++i) memMSG[i].clear();
    char tmp[160];
    int td;
    Tmessage ttMSG;
    FILE *fp=fopen(fileName,"r");
    if (fp){
        while (fread(tmp,159,1,fp)){
            fscanf(fp,"%d",&td);
            fgetc(fp);
            ttMSG.makeMessage(tmp);
            if (td==SEND)
                memMSG[ttMSG.addrID].push_back(make_pair(ttMSG,td));
            if (td==RECV)
                memMSG[ttMSG.selfID].push_back(make_pair(ttMSG,td));
            printf("history message:\n");
            ttMSG.outputMsg();
        }
    }
    fclose(fp);
}

void Tmemory::add(const Tmessage &iptMSG,int td){
    if (td==SEND){
        if (iptMSG.addrID==0) return;
        memMSG[iptMSG.addrID].push_back(make_pair(iptMSG,td));
    }
    if (td==RECV){
        if (iptMSG.selfID==0) return;
        memMSG[iptMSG.selfID].push_back(make_pair(iptMSG,td));
    }
};

