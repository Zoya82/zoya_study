#pragma once

#include "cocos2d.h"
#include <memory>

class GameController; // 前向声明

class HelloWorld : public cocos2d::Layer {
public:
    // 创建并返回 Scene
    static cocos2d::Scene* createScene();

    // 初始化
    virtual bool init() override;

    // 宏：生成 create() 静态方法
    CREATE_FUNC(HelloWorld);

private:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void addUndoShortcut(); // 绑定 U 键撤销

    std::unique_ptr<GameController> _controller; // 游戏控制器
};
