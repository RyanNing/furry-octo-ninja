// Tmessage��
#pragma once
#include <ctime>

// Tmessage�࣬����˳��̶����ں���ѹ����
class Tmessage {
private:
	char index;		// ��ǰ��Ϣ��������Ϣ�ĵڼ���
	char all;		// ����������Ϣһ�����ָ�ɼ���
	const static int size = 159;
public:
    char msg[70 * 2 + 1]; // �洢������Ϣ������������70�������ַ�
    time_t time;
    int addrID;	// address id ��ʾĿ�ĵص�id����8λ��ʾ
	int selfID;	// self id ��ʾ�Լ������ͷ�����id����8λ��ʾ

    Tmessage(const Tmessage &i);
    Tmessage(int mid,int id);
    Tmessage(){};
	Tmessage(int l, int r, int _index,int _all, char *m,time_t t,int id,int mid);//����ѳ���Ϣѹ����70�ַ����ڵ�������Tmessage

    char* toShow_2();
    char * toShow();
	char * toChar();	//��һ����׼���ȵ�Tmessageѹ���ɷ��ʹ�
	Tmessage (char *m);	//��һ�����ʹ���ԭ�ɱ�׼���ȵ�Tmessage
	void makeMessage (char *m);
	void outputMsg();	//��ʽ����ʾһ��Tmessage������
	int getID(){return addrID;};
};
