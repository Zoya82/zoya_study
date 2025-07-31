#pragma once

#include <easyx.h>

struct scene {                                         //场景基础对象
	void (*draw)(struct scene*);                       //绘制场景中所有精灵
	void (*update)(struct scene*);                     //更新
	void (*control)(struct scene*, ExMessage *msg);    //获取鼠标或键盘消息，进而控制场景中的精灵
	bool (*isQuit)(struct scene*),(*isWindow)(struct scene*);                     //指示该场景是否结束
};