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

    // Playfield ��
    for (const auto& cardModel : _gameModel->getPlayfieldCards()) {
        auto cardView = CardView::create(cardModel);
        _gameView->addChild(cardView);
        _modelViewMap[cardModel->getId()] = cardView;

        auto controller = new CardController(cardModel, cardView);
        controller->setClickCallback([this](std::shared_ptr<CardModel> model, CardView* view) {
            this->tryReplaceTopWith(model, view);
            });
    }

    // ���ƶ���
    if (auto top = _gameModel->getTopTrayCard()) {
        auto topView = CardView::create(top);
        _gameView->addChild(topView);
        _modelViewMap[top->getId()] = topView;
        new CardController(top, topView); // ��ѡ�ص�
    }
}

void GameController::tryReplaceTopWith(std::shared_ptr<CardModel> clickedCard, CardView* clickedView) {
    auto topCard = _gameModel->getTopTrayCard();
    if (!topCard) return;

    if (!MatchRuleService::canMatch(*clickedCard, *topCard)) {
        CCLOG("ƥ��ʧ�ܣ��������1");
        return;
    }

    // ����ԭ״̬
    Vec2 clickedPos = clickedCard->getPosition();
    Vec2 topPos = topCard->getPosition();
    auto previousTop = topCard;
    auto previousClicked = clickedCard;

    // �Ӿ���������
    clickedView->playMoveTo(topPos, nullptr);
    if (_modelViewMap.count(topCard->getId())) {
        _modelViewMap[topCard->getId()]->playMoveTo(clickedPos, nullptr);
    }

    // �߼����������ƶ������ clickedCard
    topCard->setPosition(clickedPos);
    clickedCard->setPosition(topPos);
    _gameModel->setTopTrayCard(clickedCard);

    // ��¼ undo
    UndoRecord record;
    record.undoAction = [this, previousTop, previousClicked, topPos, clickedPos]() {
        // �ָ�λ�úͶ�������
        previousTop->setPosition(topPos);
        previousClicked->setPosition(clickedPos);
        _gameModel->setTopTrayCard(previousTop);
        // Ҳ���Է��򶯻���ʡ�ԣ�
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
