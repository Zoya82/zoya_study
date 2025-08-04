#include "HelloWorldScene.h"
#include "views/CardView.h"
#include "models/CardModel.h"
#include "models/CardDefs.h"
#include "controllers/GameController.h"

USING_NS_CC;

static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("������Ҫ����Դ��ǰ���� 'res/' �����·��\n");
}

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create(); // CREATE_FUNC ����
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init() {
    if (!Layer::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ʾ��������һ�ź��� A ���ƣ����� CardDefs.h ���� CFT_ACE��
    auto model = std::make_shared<CardModel>(CST_HEARTS, CFT_ACE);
    auto card = CardView::create(model);
    card->setPosition(origin + visibleSize / 2);
    this->addChild(card);

    addUndoShortcut();

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();
}

void HelloWorld::addUndoShortcut() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_U) {
            if (_controller) {
                _controller->undoLast();
            }
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
