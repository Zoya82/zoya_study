#pragma once
#include "cocos2d.h"

enum CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

enum CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,
    CST_DIAMONDS,
    CST_HEARTS,
    CST_SPADES,
    CST_NUM_CARD_SUIT_TYPES
};

/**
 * @brief 运行时卡牌数据模型
 */
class CardModel {
public:
    CardModel(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2& pos);

    int getId() const;
    CardFaceType getFace() const;
    CardSuitType getSuit() const;
    const cocos2d::Vec2& getPosition() const;
    void setPosition(const cocos2d::Vec2& pos);

private:
    int _id;
    CardFaceType _face;
    CardSuitType _suit;
    cocos2d::Vec2 _position;
};
