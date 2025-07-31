#pragma once

#include "scene.h"

struct account {
	struct scene super;                 //加载刚才的图片
	RECT rectHead,rectName,rectNametext, rectRegister,rectRegistertext,rectFinish;        //标题，用户名，用户名文本框，注册，注册文本框矩形区域
	bool isNametextHover, isRegistertextHover;  //鼠标是否悬停在用户名、注册文本框上
	bool isFinish;                            //场景是否退出，初始为false，回车后改变为true
};

void accountInit(struct account* s);
void accountDraw(struct account* s);
bool accountIsFinish(struct account* s);
void accountControl(struct account* s, ExMessage* msg);