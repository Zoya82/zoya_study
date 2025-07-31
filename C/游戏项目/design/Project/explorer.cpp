#include "explorer.h"
#include "image.h"
#include <stdio.h>

enum explorerStatus explorerStatusSqauence[5] = {                  //枚举探索者状态
	explorer_normal0,
	explorer_down0,
	explorer_down1,
	explorer_down2,
	explorer_destroy
};

void explorerDraw(struct explorer* h) {                                                       //explorerDraw函数
	putTransparentImage(h->super.x, h->super.y,
		h->imgArrExplorerMask[h->status],
		h->imgArrExplorer[h->status]);
}

void explorerUpdate(struct explorer* h) {                                                          //explorerUpdate函数
	h->explorerUpdateCnt++;

	if (h->explorerUpdateCnt >= 15) {
		h->explorerUpdateCnt = 0;
		if (h->life == 0) {
			if (h->status < explorer_destroy){
				printf("Current status: %d\n", h->status);
				h->status = explorerStatusSqauence[h->status + 1];
				printf("New status: %d\n", h->status);
				}
		}
	}
}

void explorerDestroy(struct explorer* h) {
	for (int i = 0; i < 4; i++) {
		if (h->imgArrExplorer[i] != nullptr) {
			delete h->imgArrExplorer[i];
			h->imgArrExplorer[i] = nullptr;
		}
		if (h->imgArrExplorerMask[i] != nullptr) {
			delete h->imgArrExplorerMask[i];
			h->imgArrExplorerMask[i] = nullptr;
		}
	}
}

void explorerInit(struct explorer *h) {                            //探索者初始化
	h->super.draw = (void(*)(struct sprite*))explorerDraw;         //explorerDraw指针函数转为指针赋给对象父类方法
	h->super.update = (void(*)(struct sprite*))explorerUpdate;     //同上，更新方法

	h->explorerUpdateCnt = 0;                                      //初始化探索者
	h->status = explorer_normal0;
	h->life = 1;

	h->super.x = 100;
	h->super.y = 360;

	for (int i = 0; i < 4; i++) {                                   //用new创建IMAGE对象
		h->imgArrExplorer[i] = new IMAGE;
		h->imgArrExplorerMask[i] = new IMAGE;
	}

	char imgPath[50];
	char imgMaskPath[50];

	snprintf(imgPath,sizeof(imgPath), "gamepicture\\explorer\\explorer0.png");              //探索者正常状态图片
	snprintf(imgMaskPath, sizeof(imgMaskPath),"gamepicture\\explorer\\explorer0_mask.png");
	loadimage(h->imgArrExplorer[0], imgPath);
	loadimage(h->imgArrExplorerMask[0], imgMaskPath);

	for (int i = 0; i <= 2; i++) {
		snprintf(imgPath,sizeof(imgPath), "gamepicture\\explorer\\explorer_down%d.png",i);   //探索者被击毁图片
		snprintf(imgMaskPath, sizeof(imgPath),"gamepicture\\explorer\\explorer%d_mask.png",i);
		loadimage(h->imgArrExplorer[i+1], imgPath);
		loadimage(h->imgArrExplorerMask[i+1], imgMaskPath);
	}
}
