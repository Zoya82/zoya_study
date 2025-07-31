#pragma once
#include "vector.h"

struct soundManager {                                    //管理一个音频的多个实例
	void (*play)(struct soundManager*);                  //打开并播放一个音频实例
	void (*close)(struct soundManager* e, int interval); //关闭所有已播放完成的音频实例，interval为播放时长，用于判断音频是否播放完成

	vector vecSoundAlias;                                //记录所有音频实例的别名
	char soundPath[100];                                 //音频文件的路径
};

void soundManagerInit(struct soundManager*, const char*);
void soundManagerDestroy(struct soundManager*);