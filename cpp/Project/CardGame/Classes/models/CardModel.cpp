#include "CardModel.h"

CardModel::CardModel(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2& pos)
    : _id(id), _face(face), _suit(suit), _position(pos) {
}

int CardModel::getId() const { return _id; }
CardFaceType CardModel::getFace() const { return _face; }
CardSuitType CardModel::getSuit() const { return _suit; }
const cocos2d::Vec2& CardModel::getPosition() const { return _position; }
void CardModel::setPosition(const cocos2d::Vec2& pos) { _position = pos; }
