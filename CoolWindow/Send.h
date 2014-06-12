#pragma once
#include "Tmessage.h"

class Send {
private:
	char *msg; // 存储具体消息，没有长度限制
	Tmessage * all_msg[256];	//作为输出，存储指向每一段Tmessage对象的指针
	char all; // 总共分成几段
public:
	Send (){};
	void init(char *s, int id, time_t tt=0);	//接受目标id，分割并构造若干条Tmessage类
	void send();
	void testOutput();	//测试输出
};

