#pragma once
#include "cocos2d.h"

/**
 * @brief ������Ϸ����ͼ���������԰������������
 */
class GameView : public cocos2d::Layer {
public:
    static GameView* create();
    virtual bool init() override;
};
