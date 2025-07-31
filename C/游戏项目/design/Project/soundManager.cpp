#include "soundmanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <stdint.h>
#include <Windows.h>

void soundPlay(struct soundManager* e)
{
	int currentTime = GetTickCount();                       //获取系统的启动毫秒时
	int* pAlias = (int*)malloc(sizeof(int));
	if (pAlias == NULL)
		return;
	*pAlias = currentTime;
	e->vecSoundAlias.append(&e->vecSoundAlias, pAlias);     //将当前时间记录到数组中

	char command[100];                                      //使用当前时间作为音频实例的别名，使用别名播放音频
	sprintf_s(command, sizeof(command), "open %s alias %d", e->soundPath, currentTime);
	mciSendString(command, NULL, 0, NULL);
	sprintf_s(command, sizeof(command), "play %d", currentTime);
	mciSendString(command, NULL, 0, NULL);
}

void soundClose(struct soundManager* e, int interval)
{
	int currentTime = GetTickCount();                        //获得系统启动毫秒时
	char command[100];
	for (int i = 0; i < e->vecSoundAlias.size; i++)
	{
		int* pAlias = (int*)e->vecSoundAlias.get(&e->vecSoundAlias, i);  //数组存储的既是别名，也是创建音频实例的时间
		if (currentTime - *pAlias < interval)                //用currentTime与数组中元素所指向的值相减，即可计算出某一音频实例实际存在的时间
			continue;
		sprintf_s(command,sizeof(command), "close %d", *pAlias);
		mciSendString(command, NULL, 0, NULL);
		free(pAlias);
		pAlias = NULL; // 将指针设置为 NULL
		e->vecSoundAlias.remove(&e->vecSoundAlias, i);
		i--;
	}
}

void soundManagerInit(struct soundManager* e, const char* soundPath)
{
	e->play = soundPlay;
	e->close = soundClose;

	vectorInit(&e->vecSoundAlias);
	strcpy_s(e->soundPath, soundPath);
}

void soundManagerDestroy(struct soundManager* e)
{
	char command[100];
	for (int i = 0; i < e->vecSoundAlias.size; i++)
	{
		int* pAlias = (int*)e->vecSoundAlias.get(&e->vecSoundAlias, i);
		sprintf_s(command, sizeof(command), "close %d", *pAlias);
		mciSendString(command, NULL, 0, NULL);
		free(pAlias);
	}
	vectorDestroy(&e->vecSoundAlias);
}