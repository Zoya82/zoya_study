#include "soundmanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <stdint.h>
#include <Windows.h>

void soundPlay(struct soundManager* e)
{
	int currentTime = GetTickCount();                       //��ȡϵͳ����������ʱ
	int* pAlias = (int*)malloc(sizeof(int));
	if (pAlias == NULL)
		return;
	*pAlias = currentTime;
	e->vecSoundAlias.append(&e->vecSoundAlias, pAlias);     //����ǰʱ���¼��������

	char command[100];                                      //ʹ�õ�ǰʱ����Ϊ��Ƶʵ���ı�����ʹ�ñ���������Ƶ
	sprintf_s(command, sizeof(command), "open %s alias %d", e->soundPath, currentTime);
	mciSendString(command, NULL, 0, NULL);
	sprintf_s(command, sizeof(command), "play %d", currentTime);
	mciSendString(command, NULL, 0, NULL);
}

void soundClose(struct soundManager* e, int interval)
{
	int currentTime = GetTickCount();                        //���ϵͳ��������ʱ
	char command[100];
	for (int i = 0; i < e->vecSoundAlias.size; i++)
	{
		int* pAlias = (int*)e->vecSoundAlias.get(&e->vecSoundAlias, i);  //����洢�ļ��Ǳ�����Ҳ�Ǵ�����Ƶʵ����ʱ��
		if (currentTime - *pAlias < interval)                //��currentTime��������Ԫ����ָ���ֵ��������ɼ����ĳһ��Ƶʵ��ʵ�ʴ��ڵ�ʱ��
			continue;
		sprintf_s(command,sizeof(command), "close %d", *pAlias);
		mciSendString(command, NULL, 0, NULL);
		free(pAlias);
		pAlias = NULL; // ��ָ������Ϊ NULL
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