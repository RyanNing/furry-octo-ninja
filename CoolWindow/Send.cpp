#include "Send.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include "Tsocket.h"
#include "Tmemory.h"
#include <gtk/gtk.h>
//#include "Tsave.h"

using namespace std;

void Send::init(char *s, int id,time_t tt) {
    extern Tsocket CONN;
	msg = s;
	int count = 0;		// 用于统计字符
	int l = 0, r = 0;		// 标记本段消息的开始(l)和结束(r)，
	char _index = 0, _all = 0;
	time_t t;
    if (tt==0){
        time(&t);
        puts("UUUUUUP");
    }
	else{
        t=tt;
        puts("DDDDDDN");
	}

	while (msg[r] != '\0') {
		if (msg[r] >= 0) count = count +2;
		else count = count + 1;
		r++;
	}

	_all = (count - 1) / 140 + 1;	//count-1 是为了防止正好70个字符的情况
	all = _all;
	count = 0;
	r = 0;

	while (msg[r] != '\0') {
		if (msg[r] >= 0) count = count +2;
		else count = count + 1;

		if (count > 140) {	//如果>70个字符再执行，此时右标位于下一个起始端,不要复制进去了
			_index++;
			Tmessage *m = new Tmessage(l,r,_index,_all,msg,t,id,CONN.ID);
			all_msg[_index - 1] = m;
			l = r;
			count = count - 140;
		}
		r++;
	}
	_index++;
	Tmessage *m = new Tmessage(l,r,_index,_all,msg,t,id,CONN.ID);
	all_msg[_index - 1] = m;
	//testOutput();
	send();
}


void Send::send () {
    extern char output2[600];
    extern bool check3;
    extern void refresh_right_2();
    extern Tmemory MEM;
    extern Tsocket CONN;
    // extern vector <char*> vec[9001];
    extern int now_id;
	for (int i = 0; i < all; i++){
        all_msg[i]->outputMsg();
        MEM.add(*all_msg[i],SEND);
        output2[0]=0;
        strcpy(output2,all_msg[i]->toShow());
        refresh_right_2();
		CONN.MSGsend(*all_msg[i]);
		//int id = all_msg[i]->getID();
		//char *oneMsg = all_msg[i]->toChar();
	//	vec[id - 1000].push_back(oneMsg);
	}
}

//test
void Send::testOutput() {
	printf("--------------------本条消息一共有%d段-----------------------\n\n",all);
	for (int i = 0; i < all; i++){
		all_msg[i]->outputMsg();
		printf("\n");
	}
	printf("----------------------------end------------------------------\n\n");
}

