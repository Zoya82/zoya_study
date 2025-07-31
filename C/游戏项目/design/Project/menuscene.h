#pragma once

#include "scene.h"

struct menuScene {
	struct scene super;
	IMAGE* bk;                               //���ظղŵ�ͼƬ
	RECT rectStartGame, rectEndGame,rectRegister;        //��ʼ��������ť��������
	bool isStartGameHover, isEndGameHover,isRegisterHover;  //����Ƿ���ͣ�ڿ�ʼ��������ť��
	bool isQuit,isWindow;                            //�����Ƿ��˳�����ʼΪfalse�����¿�ʼ��ı�Ϊtrue
};

void menuSceneInit(struct menuScene* s);
void menuSceneDestroy(struct menuScene* s);