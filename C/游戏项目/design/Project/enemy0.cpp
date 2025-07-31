#include "enemy.h"
#include "enemy0.h"
#include "image.h"
#include <stdio.h>

void enemy0Destroy(struct enemy0* e) {
	for (int i = 0; i < 3; i++) {
		delete e->super.imgArrEnemy[i];
		delete e->super.imgArrEnemyMask[i];
	}
	free(e->super.imgArrEnemy);
	free(e->super.imgArrEnemyMask);
}

void enemy0Init(struct enemy0* e) {
	enemyInit((struct enemy *)e);
	e->super.destroy = (void(*)(struct enemy*))enemy0Destroy;

	e->super.super.width = 150;
	e->super.super.height = 120;
	e->super.enemyType = enemyType0;
	e->super.life = 1;
	e->super.lastStatusBeforeDestroy = enemy_down1;

	e->super.imgArrEnemy = (IMAGE**)malloc(sizeof(IMAGE*) * 3);
	e->super.imgArrEnemyMask = (IMAGE**)malloc(sizeof(IMAGE*) * 3);
	for (int i = 0; i < 3; i++) {
		e->super.imgArrEnemy[i] = new IMAGE;
		e->super.imgArrEnemyMask[i] = new IMAGE;
	}

	loadimage(e->super.imgArrEnemy[0], "gamepicture\\enemy0\\enemy0.png");
	loadimage(e->super.imgArrEnemyMask[0], "gamepicture\\enemy0\\enemy0_mask.png");

	char imgPath[50];
	char imgMaskPath[50];
	for (int i = 0; i < 2; i++) {
		sprintf_s(imgPath, sizeof(imgPath), "gamepicture\\enemy0\\enemy0_dowm%d.png", i);
		sprintf_s(imgMaskPath, sizeof(imgMaskPath), "gamepicture\\enemy0\\enemy0_dowm%d_mask.png", i);
		loadimage(e->super.imgArrEnemy[i + 1], imgPath);
		loadimage(e->super.imgArrEnemyMask[i + 1], imgMaskPath);
	}
}

