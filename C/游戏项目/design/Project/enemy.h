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
	void (*hited)(struct enemy *);     //敌机被击中后处理
	void (*destroy)(struct enemy*);    //销毁敌机

	IMAGE** imgArrEnemy;
	IMAGE** imgArrEnemyMask;
	enum enemyType enemyType;          //记录敌机种类
	int v;                             //敌机速度
	int life;                          //生命值
	int enemyDownCnt;                  //爆炸状态计数器
	int status;                        //记录敌机状态
	int lastStatusBeforeDestroy;       //销毁前的最后状态
};

void enemyInit(struct enemy *);
