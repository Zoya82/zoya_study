#include "background.h"

void backgroundDraw(struct background* b) {
	putimage(b->xA, 0, b->imgBackground_middle);
	putimage(b->xB, 0, b->imgBackground_middle);
}

void backgroundUpdate(struct background* b) {
	b->xA = b->xA - 1;
	b->xB = b->xB - 1;
	if (b->xA <= 0) {
		b->xA = 1280;
		b->xB = 0;
	}
}

void backgroundInit(struct background* b) {
	b->super.draw = (void(*)(struct sprite*))backgroundDraw;
	b->super.update = (void(*)(struct sprite*))backgroundUpdate;

	b->xA = 1280;
	b->xB = 0;

	b->imgBackground_middle = new IMAGE;
	loadimage(b->imgBackground_middle, "gamepicture\\background\\background_middle.png");
}

void backgroundDestroy(struct background* b) {
	delete b->imgBackground_middle;
}