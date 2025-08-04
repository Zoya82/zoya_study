#pragma once

#include "cocos2d.h"
#include <memory>

class GameController; // ǰ������

class HelloWorld : public cocos2d::Layer {
public:
    // ���������� Scene
    static cocos2d::Scene* createScene();

    // ��ʼ��
    virtual bool init() override;

    // �꣺���� create() ��̬����
    CREATE_FUNC(HelloWorld);

private:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void addUndoShortcut(); // �� U ������

    std::unique_ptr<GameController> _controller; // ��Ϸ������
};
