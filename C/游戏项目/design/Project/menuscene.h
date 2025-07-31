#pragma once

#include "scene.h"

struct menuScene {
	struct scene super;
	IMAGE* bk;                               //加载刚才的图片
	RECT rectStartGame, rectEndGame,rectRegister;        //开始，结束按钮矩形区域
	bool isStartGameHover, isEndGameHover,isRegisterHover;  //鼠标是否悬停在开始，结束按钮上
	bool isQuit,isWindow;                            //场景是否退出，初始为false，按下开始后改变为true
};

void menuSceneInit(struct menuScene* s);
void menuSceneDestroy(struct menuScene* s);