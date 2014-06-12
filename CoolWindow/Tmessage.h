// Tmessage类
#pragma once
#include <ctime>

// Tmessage类，变量顺序固定用于后面压缩串
class Tmessage {
private:
	char index;		// 当前消息是完整消息的第几段
	char all;		// 本条完整消息一共被分割成几段
	const static int size = 159;
public:
    char msg[70 * 2 + 1]; // 存储具体消息，长度限制在70个中文字符
    time_t time;
    int addrID;	// address id 表示目的地的id，用8位表示
	int selfID;	// self id 表示自己（发送方）的id，用8位表示

    Tmessage(const Tmessage &i);
    Tmessage(int mid,int id);
    Tmessage(){};
	Tmessage(int l, int r, int _index,int _all, char *m,time_t t,int id,int mid);//用与把长消息压缩成70字符以内的若干条Tmessage

    char* toShow_2();
    char * toShow();
	char * toChar();	//把一条标准长度的Tmessage压缩成发送串
	Tmessage (char *m);	//把一条发送串还原成标准长度的Tmessage
	void makeMessage (char *m);
	void outputMsg();	//格式化显示一条Tmessage的内容
	int getID(){return addrID;};
};
