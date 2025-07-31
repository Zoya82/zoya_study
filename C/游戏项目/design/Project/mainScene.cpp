#include "mainScene.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy0.h"
#include "enemy1.h"
#include "scoreboard.h"
#include <stdio.h>

void mainSceneDraw(struct mainScene* s) {
	if (s->isPaulse == false) {
		s->vecElements.clear(&s->vecElements);           //����ն�̬�����е�����
		s->vecElements.append(&s->vecElements, s->bk);   //����Ҫ���Ƶ�Ԫ��׷�ӽ�������

		for (int i = 0; i < s->vecEnemy.size; i++)       //���Ƶл�
		{
			struct enemy* pEmemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);
			s->vecElements.append(&s->vecElements, pEmemy);
		}

		s->vecElements.append(&s->vecElements, s->explorer);  //����explorer

		for (int i = 0; i < s->vecBullets.size; i++) {   //�����ӵ�
			struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
			s->vecElements.append(&s->vecElements, pBullet);
		}

		for (int i = 0; i < s->vecElements.size; i++) {
			struct sprite* pSprite = (struct sprite*)(s->vecElements.pData[i]);
			pSprite->draw(pSprite);                       //���Ե��ø��Ծ����draw����
		}
		char buff[10];                                    //�Ʒְ�
		sprintf_s(buff, sizeof(buff), "�÷�:%d", s->mark);
		outtextxy(0, 0, buff);
	}
	else if (s->isPaulse == true) {
		putimage(0, 0, s->paulse);
	}
	

	
}

void generateNewEnemy(struct mainScene* s){
	int r = rand() % 60;                                  //���ָ���ʽ�л��ĸ���һ��60��
	struct enemy* pEnemy = NULL;


	if (0 <= r && r < 20)                                 //40/60����enemy0
	{
		struct enemy0* pEnemy0 = (struct enemy0*)malloc(sizeof(struct enemy0));
		if (pEnemy0 == NULL) {
			return;  // �������ʧ�ܣ��������أ�����������ʿ�ָ��
		}
		enemy0Init(pEnemy0);
		pEnemy = (struct enemy*)pEnemy0;
	}

	else if (20 <= r && r < 30)                          //15/60����enemy1
	{
		struct enemy1* pEnemy1 = (struct enemy1*)malloc(sizeof(struct enemy1));
		if (pEnemy1 == NULL) {
			return;  // �������ʧ�ܣ��������أ�����������ʿ�ָ��
		}
		enemy1Init(pEnemy1);
		pEnemy = (struct enemy*)pEnemy1;
	}
	else {
		// ������������������ӡ������Ϣ
		printf("Unexpected value of r: %d\n", r);
		return;
	}

	int m, n;                                            //����µл�λ��
	m = 100;
	n = 720 - 100;

	pEnemy->super.y = rand() % (n - m + 1) + m;          //y���������䡾100��620��֮�����


	if (pEnemy->enemyType == enemyType0)                 //x����
		pEnemy->super.x = 1306;
	else if (pEnemy->enemyType == enemyType1)
		pEnemy->super.x = 1339;

	s->vecEnemy.append(&s->vecEnemy, pEnemy);
}

void destroyInvalidEnemy(struct mainScene* s)
{
	for (int i = 0; i < s->vecEnemy.size; i++)               //��鲢ɾ���ɳ������״̬Ϊdestroy�ĵл�
	{
		struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, i);

		if (pEnemy == NULL) {
			continue;
		}

		if (pEnemy->super.x < 0 || pEnemy->status == enemy_destroy)
		{
			//  �����ٵĵл���������Ʒ�
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
	pBullet->super.x = s->explorer->super.x + 104;            //����explorerλ��ˢ���ӵ�λ��
	pBullet->super.y = s->explorer->super.y + 50;
	s->vecBullets.append(&s->vecBullets, pBullet);
}

void destroyInvalidBullet(struct mainScene* s) {
	if (s->vecBullets.size <= 0)                 //�������Ƿ����ӵ�
		return;
	struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, 0);    //����һ���ӵ��Ƿ�ɳ�����
	if (pBullet->super.x > 1312) {
		s->vecBullets.remove(&s->vecBullets, 0);
		bulletDestroy(pBullet);
		free(pBullet);
	}
}

void bulletHitEnemyCheck(struct mainScene* s)
{
	//  ��ײ���
	for (int i = 0; i < s->vecBullets.size; i++)
	{
		//  ���ӵ�����Ϊͷ����һ����
		struct bullet* pBullet = (struct bullet*)s->vecBullets.get(&s->vecBullets, i);
		POINT bulletPoint;
		bulletPoint.x = pBullet->super.x + 32;
		bulletPoint.y = pBullet->super.y + 7;

		//  ���ÿһ���ӵ��Ƿ���ײ������л�
		for (int j = 0; j < s->vecEnemy.size; j++)
		{
			struct enemy* pEnemy = (struct enemy*)s->vecEnemy.get(&s->vecEnemy, j);

			//  �л��Ŀ����߶�
			int width, height;
			width = pEnemy->super.width;
			height = pEnemy->super.height;

			//  �л���������
			int left, top, right, bottom;
			left = pEnemy->super.x;
			top = pEnemy->super.y;
			right = left + width;
			bottom = top + height;

			//  ����ӵ��Ƿ��ھ���������
			if (bulletPoint.x > left && bulletPoint.x < right &&
				bulletPoint.y > top && bulletPoint.y < bottom
				)
			{
				if (pEnemy->life != 0)
				{
					bulletDestroy(pBullet);                        //�ӵ�ײ�����л��������ӵ�
					free(pBullet);
					s->vecBullets.remove(&s->vecBullets, i);
					i--;
					
					pEnemy->hited(pEnemy);                         //�л�����
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
	//  hero��������
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

		//  �л���������
		RECT rectEnemy;
		rectEnemy.left = pEnemy->super.x;
		rectEnemy.top = pEnemy->super.y;
		rectEnemy.right = pEnemy->super.x + pEnemy->super.width;
		rectEnemy.bottom = pEnemy->super.y + pEnemy->super.height;

		//  �������Ƿ��ص�
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
		for (int i = 0; i < s->vecElements.size; i++) {  //����Ӣ��
			struct sprite* pSprite = (struct sprite*)s->vecElements.pData[i];
			pSprite->update(pSprite);
		}

		int n = rand() % 20;                    //��ʮ��֮һ�ĸ��ʳ����µл�
		if (n == 0) {
			generateNewEnemy(s);
		}

		destroyInvalidEnemy(s);                 //������Ч�л�

		s->bulletGenCnt++;                       //�ۼ��ӵ�����������
		if (s->bulletGenCnt >= 15) {
			generateBullet(s);                   //����һ���ӵ�
			s->bulletGenCnt = 0;                 //��������λΪ0
		}

		destroyInvalidBullet(s);                 //������Ч�ӵ�

		bulletHitEnemyCheck(s);                  //�л�������ײ���

		bool isHited = explorerHitEnemyCheck(s);     //hero��ײ�л����
		if (isHited == true)
		{
			s->explorer->life--;
			s->explorer->status = explorer_down1;

			mciSendString("open sounds/explorer_down.WAV", NULL, 0, NULL);  //����Ӣ�۱�ը����
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
			s->explorer->super.y = msg->y - 35;           //����굱ǰ������ΪӢ�۷ɻ�����
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
	s->super.draw = (void(*)(struct scene*))mainSceneDraw;          //������������ĸ��������г�ʼ��
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

	//  �Ʒְ�
	s->mark = 0;
	settextcolor(WHITE);
	settextstyle(40, 0, "����");
	setbkmode(TRANSPARENT);

	soundManagerInit(&s->enemyDownSoundMgr, "sounds/enemy_down.WAV");
	soundManagerInit(&s->backgroundSoundMgr, "sounds/background.WAV");

	mciSendString("open sounds/background.WAV", NULL, 0, NULL);        //���ű�������
	mciSendString("play sounds/background.WAV repeat", NULL, 0, NULL); //repeat������ѭ������

	s->isPaulse = false;
}

void mainSceneDestroy(struct mainScene* s) {
	mciSendString("close sounds/background.WAV", NULL, 0, NULL);        //����������ʱ�رձ�������
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
