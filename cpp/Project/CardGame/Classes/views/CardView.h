#pragma once
#include "cocos2d.h"
#include "../models/CardModel.h"

/**
 * @brief ��չʾ���ƣ��� model����������ʾ����������ҵ�����
 */
class CardView : public cocos2d::Node {
public:
    static CardView* create(std::shared_ptr<CardModel> model);

    void updateFromModel();
    void setClickCallback(const std::function<void(std::shared_ptr<CardModel>)>& cb);
    void playMoveTo(const cocos2d::Vec2& target, const std::function<void()>& onComplete);

private:
    bool initWithModel(std::shared_ptr<CardModel> model);

    std::shared_ptr<CardModel> _model;
    cocos2d::Label* _label = nullptr;
    std::function<void(std::shared_ptr<CardModel>)> _clickCallback;
};
