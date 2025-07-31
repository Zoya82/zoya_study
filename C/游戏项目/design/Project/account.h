#pragma once

#include "scene.h"

struct account {
	struct scene super;                 //���ظղŵ�ͼƬ
	RECT rectHead,rectName,rectNametext, rectRegister,rectRegistertext,rectFinish;        //���⣬�û������û����ı���ע�ᣬע���ı����������
	bool isNametextHover, isRegistertextHover;  //����Ƿ���ͣ���û�����ע���ı�����
	bool isFinish;                            //�����Ƿ��˳�����ʼΪfalse���س���ı�Ϊtrue
};

void accountInit(struct account* s);
void accountDraw(struct account* s);
bool accountIsFinish(struct account* s);
void accountControl(struct account* s, ExMessage* msg);