#include "GameController.h"
#include "../configs/loaders/LevelConfigLoader.h"
#include "../services/GameModelFromLevelGenerator.h"
#include "../services/MatchRuleService.h"
#include "../views/CardView.h"
#include "CardController.h"
#include "cocos2d.h"

USING_NS_CC;

GameController::GameController() {}

void GameController::startGame(const std::string& levelConfigPath, Layer* parent) {
    auto levelConfig = LevelConfigLoader::loadFromFile(levelConfigPath);
    if (!levelConfig) return;

    _gameModel = GameModelFromLevelGenerator::generate(*levelConfig);
    _gameView = GameView::create();
    parent->addChild(_gameView);

    // Playfield 牌
    for (const auto& cardModel : _gameModel->getPlayfieldCards()) {
        auto cardView = CardView::create(cardModel);
        _gameView->addChild(cardView);
        _modelViewMap[cardModel->getId()] = cardView;

        auto controller = new CardController(cardModel, cardView);
        controller->setClickCallback([this](std::shared_ptr<CardModel> model, CardView* view) {
            this->tryReplaceTopWith(model, view);
            });
    }

    // 手牌顶部
    if (auto top = _gameModel->getTopTrayCard()) {
        auto topView = CardView::create(top);
        _gameView->addChild(topView);
        _modelViewMap[top->getId()] = topView;
        new CardController(top, topView); // 可选回调
    }
}

void GameController::tryReplaceTopWith(std::shared_ptr<CardModel> clickedCard, CardView* clickedView) {
    auto topCard = _gameModel->getTopTrayCard();
    if (!topCard) return;

    if (!MatchRuleService::canMatch(*clickedCard, *topCard)) {
        CCLOG("匹配失败：点数差不是1");
        return;
    }

    // 保存原状态
    Vec2 clickedPos = clickedCard->getPosition();
    Vec2 topPos = topCard->getPosition();
    auto previousTop = topCard;
    auto previousClicked = clickedCard;

    // 视觉交换动画
    clickedView->playMoveTo(topPos, nullptr);
    if (_modelViewMap.count(topCard->getId())) {
        _modelViewMap[topCard->getId()]->playMoveTo(clickedPos, nullptr);
    }

    // 逻辑交换：手牌顶部变成 clickedCard
    topCard->setPosition(clickedPos);
    clickedCard->setPosition(topPos);
    _gameModel->setTopTrayCard(clickedCard);

    // 记录 undo
    UndoRecord record;
    record.undoAction = [this, previousTop, previousClicked, topPos, clickedPos]() {
        // 恢复位置和顶部引用
        previousTop->setPosition(topPos);
        previousClicked->setPosition(clickedPos);
        _gameModel->setTopTrayCard(previousTop);
        // 也可以反向动画（省略）
        };
    record.redoAction = [this, previousTop, previousClicked, topPos, clickedPos]() {
        previousTop->setPosition(clickedPos);
        previousClicked->setPosition(topPos);
        _gameModel->setTopTrayCard(previousClicked);
        };
    _undoManager.record(record);
}

void GameController::undoLast() {
    _undoManager.undo();
}
