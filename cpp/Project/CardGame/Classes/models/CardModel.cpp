#pragma once
#include "CardDefs.h"
#include "cocos2d.h"
#include <memory>

class CardModel {
public:
    CardModel(CardSuitType suit, CardFaceType face, const cocos2d::Vec2& pos)
        : _suit(suit), _face(face), _position(pos) {}

    CardSuitType getSuit() const { return _suit; }
    CardFaceType getFace() const { return _face; }
    cocos2d::Vec2 getPosition() const { return _position; }

    void setPosition(const cocos2d::Vec2& pos) { _position = pos; }

private:
    CardSuitType _suit;
    CardFaceType _face;
    cocos2d::Vec2 _position;
};
