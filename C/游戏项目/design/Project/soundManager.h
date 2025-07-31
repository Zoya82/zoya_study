#pragma once
#include "vector.h"

struct soundManager {                                    //����һ����Ƶ�Ķ��ʵ��
	void (*play)(struct soundManager*);                  //�򿪲�����һ����Ƶʵ��
	void (*close)(struct soundManager* e, int interval); //�ر������Ѳ�����ɵ���Ƶʵ����intervalΪ����ʱ���������ж���Ƶ�Ƿ񲥷����

	vector vecSoundAlias;                                //��¼������Ƶʵ���ı���
	char soundPath[100];                                 //��Ƶ�ļ���·��
};

void soundManagerInit(struct soundManager*, const char*);
void soundManagerDestroy(struct soundManager*);