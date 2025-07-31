#pragma once
#include <easyx.h>
#include "sprite.h"

enum explorerStatus {
	explorer_normal0,
	explorer_down0,
	explorer_down1,
	explorer_down2,
	explorer_destroy
};

struct explorer {
	struct sprite super;
	IMAGE *imgArrExplorer[4];
	IMAGE *imgArrExplorerMask[4];
	enum explorerStatus status;
	int life;
	int explorerUpdateCnt;
};

void explorerInit(struct explorer *);
void explorerDestroy(struct explorer*);