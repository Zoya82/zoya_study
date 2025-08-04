#include "GameView.h"

USING_NS_CC;

GameView* GameView::create() {
    GameView* ret = new (std::nothrow) GameView();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GameView::init() {
    if (!Layer::init()) return false;
    // 基础背景或 UI 初始化
    return true;
}
