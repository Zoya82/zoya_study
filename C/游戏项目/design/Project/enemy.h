#pragma once
#include <graphics.h>
#include "sprite.h"
enum enemyType {
	enemyType0,
	enemyType1
};

enum enemyStatus {
	enemy_normal,
	enemy_down0,
	enemy_down1,
	enemy_destroy
};

struct enemy {
	struct sprite super;
	void (*hited)(struct enemy *);     //�л������к���
	void (*destroy)(struct enemy*);    //���ٵл�

	IMAGE** imgArrEnemy;
	IMAGE** imgArrEnemyMask;
	enum enemyType enemyType;          //��¼�л�����
	int v;                             //�л��ٶ�
	int life;                          //����ֵ
	int enemyDownCnt;                  //��ը״̬������
	int status;                        //��¼�л�״̬
	int lastStatusBeforeDestroy;       //����ǰ�����״̬
};

void enemyInit(struct enemy *);
