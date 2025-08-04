#pragma once
#include "cocos2d.h"

/**
 * @brief 整个游戏主视图容器（可以包含多个子区）
 */
class GameView : public cocos2d::Layer {
public:
    static GameView* create();
    virtual bool init() override;
};
