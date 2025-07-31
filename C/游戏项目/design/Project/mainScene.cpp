#include "mainScene.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy0.h"
#include "enemy1.h"
#include "scoreboard.h"
#include <stdio.h>

void mainSceneDraw(struct mainScene* s) {
	if (s->isPaulse == false) {
		s->vecElements.clear(&s->vecElements);           //先清空动态数组中的数据
		s->vecElements.append(&s->vecElements, s->bk);   //把需要绘制的元素追加进入数组

		for (int i = 0; i < s->vecEnemy.size; i++)       //绘制敌机
		{
			struct enemy* pEmemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
			s->vecElements.append(&s->vecElements, pEmemy);
		}

		s->vecElements.append(&s->vecElements, s->explorer);  //绘制explorer

		for (int i = 0; i < s->vecBullets.size; i++) {   //绘制子弹
			struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
			s->vecElements.append(&s->vecElements, pBullet);
		}

		for (int i = 0; i < s->vecElements.size; i++) {
			struct sprite* pSprite = (struct sprite*)(s->vecElements.pData[i]);
			pSprite->draw(pSprite);                       //可以调用各自精灵的draw方法
		}
		char buff[10];                                    //计分板
		sprintf_s(buff, sizeof(buff), "得分:%d", s->mark);
		outtextxy(0, 0, buff);
	}
	else if (s->isPaulse == true) {
		putimage(0, 0, s->paulse);
	}
	

	
}

void generateNewEnemy(struct mainScene* s){
	int r = rand() % 60;                                  //出现各样式敌机的概率一共60份
	struct enemy* pEnemy = NULL;


	if (0 <= r && r < 20)                                 //40/60出现enemy0
	{
		struct enemy0* pEnemy0 = (struct enemy0*)malloc(sizeof(struct enemy0));
		if (pEnemy0 == NULL) {
			return;  // 如果分配失败，立即返回，避免后续访问空指针
		}
		enemy0Init(pEnemy0);
		pEnemy = (struct enemy*)pEnemy0;
	}

	else if (20 <= r && r < 30)                          //15/60出现enemy1
	{
		struct enemy1* pEnemy1 = (struct enemy1*)malloc(sizeof(struct enemy1));
		if (pEnemy1 == NULL) {
			return;  // 如果分配失败，立即返回，避免后续访问空指针
		}
		enemy1Init(pEnemy1);
		pEnemy = (struct enemy*)pEnemy1;
	}
	else {
		// 处理其他情况，例如打印错误消息
		printf("Unexpected value of r: %d\n", r);
		return;
	}

	int m, n;                                            //随机新敌机位置
	m = 100;
	n = 720 - 100;

	pEnemy->super.y = rand() % (n - m + 1) + m;          //y坐标在区间【100，620】之内随机


	if (pEnemy->enemyType == enemyType0)                 //x坐标
		pEnemy->super.x = 1306;
	else if (pEnemy->enemyType == enemyType1)
		pEnemy->super.x = 1339;

	s->vecEnemy.append(&s->vecEnemy, pEnemy);
}

void destroyInvalidEnemy(struct mainScene* s)
{
	for (int i = 0; i < s->vecEnemy.size; i++)               //检查并删除飞出窗体或状态为destroy的敌机
	{
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);

		if (pEnemy == NULL) {
			continue;
		}

		if (pEnemy->super.x < 0 || pEnemy->status == enemy_destroy)
		{
			//  将击毁的敌机按照种类计分
			if (pEnemy->status == enemy_destroy)
			{
				switch (pEnemy->enemyType)
				{
				case enemyType0: s->mark += 10; break;
				case enemyType1: s->mark += 30; break;
				}
			}

			s->vecEnemy.remove(&s->vecEnemy, i);
			pEnemy->destroy(pEnemy);
			free(pEnemy);
			i--;
		}
	}
}

void generateBullet(struct mainScene* s) {
	struct bullet* pBullet = (struct bullet*)malloc(sizeof(struct bullet));
	if (pBullet == NULL) {
		return;
	}

	bulletInit(pBullet);
	pBullet->super.x = s->explorer->super.x + 104;            //根据explorer位置刷新子弹位置
	pBullet->super.y = s->explorer->super.y + 50;
	s->vecBullets.append(&s->vecBullets, pBullet);
}

void destroyInvalidBullet(struct mainScene* s) {
	if (s->vecBullets.size <= 0)                 //场景内是否有子弹
		return;
	struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, 0);    //检查第一个子弹是否飞出窗体
	if (pBullet->super.x > 1312) {
		s->vecBullets.remove(&s->vecBullets, 0);
		bulletDestroy(pBullet);
		free(pBullet);
	}
}

void bulletHitEnemyCheck(struct mainScene* s)
{
	//  碰撞检测
	for (int i = 0; i < s->vecBullets.size; i++)
	{
		//  将子弹抽象为头部的一个点
		struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
		POINT bulletPoint;
		bulletPoint.x = pBullet->super.x + 32;
		bulletPoint.y = pBullet->super.y + 7;

		//  检查每一颗子弹是否碰撞到任意敌机
		for (int j = 0; j < s->vecEnemy.size; j++)
		{
			struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, j);

			//  敌机的宽度与高度
			int width, height;
			width = pEnemy->super.width;
			height = pEnemy->super.height;

			//  敌机矩形区域
			int left, top, right, bottom;
			left = pEnemy->super.x;
			top = pEnemy->super.y;
			right = left + width;
			bottom = top + height;

			//  检查子弹是否在矩形区域内
			if (bulletPoint.x > left && bulletPoint.x < right &&
				bulletPoint.y > top && bulletPoint.y < bottom
				)
			{
				if (pEnemy->life != 0)
				{
					bulletDestroy(pBullet);                        //子弹撞击到敌机后，销毁子弹
					free(pBullet);
					s->vecBullets.remove(&s->vecBullets, i);
					i--;
					
					pEnemy->hited(pEnemy);                         //敌机击中
					if (pEnemy->life == 0)
						s->enemyDownSoundMgr.play(&s->enemyDownSoundMgr);
					break;
				}
			}
		}
	}
}

bool explorerHitEnemyCheck(struct mainScene* s)
{
	//  hero矩形区域
	RECT rectExplorer;
	rectExplorer.left = s->explorer->super.x + 10;
	rectExplorer.top = s->explorer->super.y + 10;
	rectExplorer.right = s->explorer->super.x + 90;
	rectExplorer.bottom = s->explorer->super.y + 70;

	for (int i = 0; i < s->vecEnemy.size; i++)
	{
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
		int enemyWidth = 0, enemyHeight = 0;
		if (pEnemy->status != enemy_normal)
			continue;

		//  敌机矩形区域
		RECT rectEnemy;
		rectEnemy.left = pEnemy->super.x;
		rectEnemy.top = pEnemy->super.y;
		rectEnemy.right = pEnemy->super.x + pEnemy->super.width;
		rectEnemy.bottom = pEnemy->super.y + pEnemy->super.height;

		//  两区域是否重叠
		if (rectExplorer.left <= rectEnemy.right && rectExplorer.right >= rectEnemy.left &&
			rectExplorer.top <= rectEnemy.bottom && rectExplorer.bottom >= rectEnemy.top)
		{
			if (s->explorer->status == explorer_normal0)
				return true;
		}
	}
	return false;
}

void mainSceneUpdate(struct mainScene* s) {
	if (s -> isPaulse == false) {
		for (int i = 0; i < s->vecElements.size; i++) {  //更新英雄
			struct sprite* pSprite = (struct sprite*)s->vecElements.pData[i];
			pSprite->update(pSprite);
		}

		int n = rand() % 20;                    //二十分之一的概率出现新敌机
		if (n == 0) {
			generateNewEnemy(s);
		}

		destroyInvalidEnemy(s);                 //销毁无效敌机

		s->bulletGenCnt++;                       //累加子弹产生计数器
		if (s->bulletGenCnt >= 15) {
			generateBullet(s);                   //产生一颗子弹
			s->bulletGenCnt = 0;                 //计数器复位为0
		}

		destroyInvalidBullet(s);                 //销毁无效子弹

		bulletHitEnemyCheck(s);                  //敌机击中碰撞检测

		bool isHited = explorerHitEnemyCheck(s);     //hero碰撞敌机检测
		if (isHited == true)
		{
			s->explorer->life--;
			s->explorer->status = explorer_down1;

			mciSendString("open sounds/explorer_down.WAV", NULL, 0, NULL);  //播放英雄爆炸音乐
			mciSendString("play sounds/explorer_down.WAV", NULL, 0, NULL);
		}

		s->soundCloseCnt++;
		if (s->soundCloseCnt >= 60)
		{
			s->enemyDownSoundMgr.close(&s->enemyDownSoundMgr, 1000);
			s->soundCloseCnt = 0;
		}
	}

	
}

void mainSceneControl(struct mainScene* s, ExMessage* msg) {
	if (s->isPaulse == false) {
		if (msg->message == WM_MOUSEMOVE) {
			s->explorer->super.x = msg->x - 35;
			s->explorer->super.y = msg->y - 35;           //把鼠标当前坐标作为英雄飞机坐标
		}
		else if (msg->message == WM_KEYUP) {
			if (msg->vkcode == VK_ESCAPE)
				s->isPaulse = true;
		}
	}
	else if (s->isPaulse == true) {
		switch (msg->message)
		{
		case WM_LBUTTONDOWN:
		{
			s->isPaulse = false;
			break;
		}
		case WM_KEYUP:
		{
			if (msg->vkcode == VK_ESCAPE)
				s->isPaulse = true; 
			break;
		}
		}
	}
	
}

bool mainSceneIsQuit(struct mainScene* s) {
	if (s->explorer->status == explorer_destroy)
		return true;
	return false;
}

void mainSceneInit(struct mainScene* s) {
	s->super.draw = (void(*)(struct scene*))mainSceneDraw;          //将场景对象的四个方法进行初始化
	s->super.update = (void(*)(struct scene*))mainSceneUpdate;
	s->super.control = (void(*)(struct scene*, ExMessage*))mainSceneControl;
	s->super.isQuit = (bool(*)(struct scene*))mainSceneIsQuit;

	s->explorer = (struct explorer *)malloc(sizeof(struct explorer));
	explorerInit(s->explorer);

	s->bulletGenCnt = 0;
	s->soundCloseCnt = 0;

	s->bk = (struct background *)malloc(sizeof(struct background));
	backgroundInit(s->bk);

	s->paulse = new IMAGE;
	loadimage(s->paulse, "gamepicture\\background\\background.png");

	vectorInit(&s->vecElements);
	vectorInit(&s->vecEnemy);
	vectorInit(&s->vecBullets);

	//  计分板
	s->mark = 0;
	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	setbkmode(TRANSPARENT);

	soundManagerInit(&s->enemyDownSoundMgr, "sounds/enemy_down.WAV");
	soundManagerInit(&s->backgroundSoundMgr, "sounds/background.WAV");

	mciSendString("open sounds/background.WAV", NULL, 0, NULL);        //播放背景音乐
	mciSendString("play sounds/background.WAV repeat", NULL, 0, NULL); //repeat参数，循环播放

	s->isPaulse = false;
}

void mainSceneDestroy(struct mainScene* s) {
	mciSendString("close sounds/background.WAV", NULL, 0, NULL);        //主场景销毁时关闭背景音乐
	mciSendString("close sounds/hero_down.WAV", NULL, 0, NULL);

	soundManagerDestroy(&s->enemyDownSoundMgr);

	if (s->explorer != NULL) {
		explorerDestroy(s->explorer);
		free(s->explorer);
	}

	if (s->bk != NULL) {
		backgroundDestroy(s->bk);
		free(s->bk);
	}

	vectorDestroy(&s->vecElements);

	for (int i = 0; i < s->vecEnemy.size; i++)
	{
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
		if (pEnemy != NULL) {
			pEnemy->destroy(pEnemy);
			free(pEnemy);
		}
	}
	vectorDestroy(&s->vecEnemy);

	for (int i = 0; i < s->vecBullets.size; i++) {
		struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
		bulletDestroy(pBullet);
		free(pBullet);
	}
	vectorDestroy(&s->vecBullets);

	delete s->paulse;
}
