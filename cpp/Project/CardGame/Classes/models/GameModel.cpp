#include "GameModel.h"

void GameModel::addPlayfieldCard(std::shared_ptr<CardModel> card) {
    _playfieldCards.push_back(card);
}

void GameModel::setTopTrayCard(std::shared_ptr<CardModel> card) {
    _trayTopCard = card;
}

std::shared_ptr<CardModel> GameModel::getTopTrayCard() const {
    return _trayTopCard;
}

const std::vector<std::shared_ptr<CardModel>>& GameModel::getPlayfieldCards() const {
    return _playfieldCards;
}
