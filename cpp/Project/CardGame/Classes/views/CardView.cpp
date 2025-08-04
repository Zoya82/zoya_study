#include "CardView.h"

USING_NS_CC;

CardView* CardView::create(std::shared_ptr<CardModel> model) {
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->initWithModel(model)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool CardView::initWithModel(std::shared_ptr<CardModel> model) {
    _model = model;
    // 简单表示：用数字 label 代表点数
    _label = Label::createWithSystemFont(std::to_string(static_cast<int>(_model->getFace())), "Arial", 48);
    this->addChild(_label);
    this->setPosition(_model->getPosition());
    // 触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        Vec2 loc = this->convertToNodeSpace(touch->getLocation());
        Rect bBox = this->getBoundingBox();
        if (bBox.containsPoint(touch->getLocation())) {
            if (_clickCallback) _clickCallback(_model);
            return true;
        }
        return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void CardView::updateFromModel() {
    // 同步位置/文本等
    this->setPosition(_model->getPosition());
    _label->setString(std::to_string(static_cast<int>(_model->getFace())));
}

void CardView::setClickCallback(const std::function<void(std::shared_ptr<CardModel>)>& cb) {
    _clickCallback = cb;
}

void CardView::playMoveTo(const Vec2& target, const std::function<void()>& onComplete) {
    auto move = MoveTo::create(0.2f, target);
    auto seq = Sequence::create(move, CallFunc::create([this, onComplete]() {
        if (onComplete) onComplete();
        }), nullptr);
    this->runAction(seq);
}
