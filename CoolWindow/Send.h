#pragma once
#include "Tmessage.h"

class Send {
private:
	char *msg; // �洢������Ϣ��û�г�������
	Tmessage * all_msg[256];	//��Ϊ������洢ָ��ÿһ��Tmessage�����ָ��
	char all; // �ܹ��ֳɼ���
public:
	Send (){};
	void init(char *s, int id, time_t tt=0);	//����Ŀ��id���ָ����������Tmessage��
	void send();
	void testOutput();	//�������
};

