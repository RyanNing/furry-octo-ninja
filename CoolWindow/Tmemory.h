#pragma once
#include "Tmessage.h"
#include <vector>
#define RECV 0
#define SEND 1
#define DELE -1

class Tmemory{
private:
    int ID;
    char fileName[20];
public:
    std::vector<std::pair<Tmessage,int> > memMSG[10000];
    Tmemory();
    ~Tmemory();
    void writeFile();
    void readFile();
    void add(const Tmessage &iptMSG,int flag);
};
