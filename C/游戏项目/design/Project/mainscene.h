#pragma once
#include "scene.h"
#include "background.h"
#include "explorer.h"
#include "vector.h"
#include "soundManager.h"

struct mainScene {
	struct scene super;
	explorer *explorer;
	background *bk;
	IMAGE* paulse;
	vector vecElements;
	vector vecEnemy;
	vector vecBullets;
	int bulletGenCnt;
	int mark;              //¼Æ·Ö
	bool isPaulse;
	soundManager enemyDownSoundMgr;
	soundManager backgroundSoundMgr;
	int soundCloseCnt;
};

void mainSceneInit(struct mainScene *s);
void mainSceneDestroy(struct mainScene *s);