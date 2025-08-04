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
    CardModel(CardSuitType suit, CardFaceType face, const cocos2d::Vec2& pos)
        : _suit(suit), _face(face), _position(pos) {
    }

    CardSuitType getSuit() const { return _suit; }
    CardFaceType getFace() const { return _face; }
    cocos2d::Vec2 getPosition() const { return _position; }

    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }

private:
    CardSuitType _suit;
    CardFaceType _face;
    cocos2d::Vec2 _position;
};