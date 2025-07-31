#include "bullet.h"
#include "image.h"

void bulletDraw(struct bullet* b) {
	putTransparentImage(b->super.x, b->super.y, b->imgBulletMask, b->imgBullet);
}

void bulletUpdate(struct bullet* b) {
	b->super.x += 8;
}

void bulletInit(struct bullet* b) {
	b->super.draw = (void (*)(struct sprite*))bulletDraw;
	b->super.update = (void(*)(struct sprite*))bulletUpdate;

	b->imgBullet = new IMAGE;
	b->imgBulletMask = new IMAGE;
	loadimage(b->imgBullet, "gamepicture\\bullet\\bullet.png");
	loadimage(b->imgBulletMask, "gamepicture\\bullet\\bullet_mask.png");
}

void bulletDestroy(struct bullet* b) {
	delete b->imgBullet;
	delete b->imgBulletMask;
}