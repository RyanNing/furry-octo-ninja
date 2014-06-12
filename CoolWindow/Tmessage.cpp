#include "Tmessage.h"
#include <stdio.h>
#include <cstring>
//#include "Tsave.h"

Tmessage::Tmessage(int mid,int id){
    msg[0]=0;
    addrID = id;
    selfID = mid;
}

char* Tmessage::toShow(){
    char t[600];
    char output[600];
    output[0]=0;
    t[0]=0;
	if (all > 1){
        t[0]=0;
		sprintf(t,"(%d/%d) ",index,all);
		strcat(output,t);
	}
	strcat(output,msg);
	return output;
}

char* Tmessage::toShow_2(){
    char t[600];
    char output[600];
    output[0]=0;
    t[0]=0;
    sprintf(t,"发件人ID：%d 收件人ID：%d 发送时间：%s\n",selfID,addrID,ctime(&time));
    strcat(output,t);
	if (all > 1){
        t[0]=0;
		sprintf(t,"(%d/%d) ",index,all);
		strcat(output,t);
	}
	strcat(output,msg);
	return output;
}

void Tmessage::outputMsg() {
	printf("发件人ID：%d 收件人ID：%d 发送时间：%s\n",selfID,addrID,ctime(&time));
	if (all > 1)
		printf("(%d/%d) ",index,all);
	puts(msg);
	puts("");
}

Tmessage::Tmessage(const Tmessage &i){
	index=i.index;
	all=i.all;
	strcpy(msg,i.msg);
    time=i.time;
    addrID=i.addrID;
	selfID=i.selfID;
}

Tmessage::Tmessage(int l, int r, int _index, int _all, char *m,time_t t, int id, int mid) {
	int i = 0;
	while (r > l) {
		msg[i++] = m[l];
		l++;
	}
	msg[i] = '\0';
	index = _index;
	all = _all;
	time = t;
	addrID = id;
	selfID = mid;
}

// 把一个类压缩成发送串
char * Tmessage::toChar(){   //得到每个Tmessage 类中的逐个字节输出
	char *m = new char [160];
	int a = addrID;
	for(int i=0;i<4;i++){
		m[i]=(char)a;
		a=a>>8;
	}
	a = selfID;
	for(int i=0;i<4;i++){
		m[i + 4]=(char)a;
		a=a>>8;
	}
	time_t b = time;
	for(int i=0;i<8;i++){
		m[i + 8]=(char)b;
		b=b>>8;
	}
	m[16] = index;
	m[17] = all;
	for (int i = 0; i < 141; i++)
		m[i + 18] = msg[i];

	return m;
}

// 从一个发送串中还原Tmessage类
void Tmessage::makeMessage(char *m) {
	memcpy(&addrID,&m[0],4);
	memcpy(&selfID,&m[4],4);
	memcpy(&time,&m[8],4);
	index = m[16];
	all = m[17];
	for (int i = 0; i < 141; i++)
		msg[i] = m[18 + i];
}

Tmessage::Tmessage(char *m) {
	makeMessage(m);
}
