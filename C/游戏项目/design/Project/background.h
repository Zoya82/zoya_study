#pragma once
#include "sprite.h"
#include <easyx.h>

struct background {
	struct sprite super;
	int xA;
	int xB;
	IMAGE* imgBackground_middle;
};

void backgroundInit(struct background*);
void backgroundDestroy(struct background*);