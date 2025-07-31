#pragma once

#include <easyx.h>

struct scene {                                         //������������
	void (*draw)(struct scene*);                       //���Ƴ��������о���
	void (*update)(struct scene*);                     //����
	void (*control)(struct scene*, ExMessage *msg);    //��ȡ���������Ϣ���������Ƴ����еľ���
	bool (*isQuit)(struct scene*),(*isWindow)(struct scene*);                     //ָʾ�ó����Ƿ����
};