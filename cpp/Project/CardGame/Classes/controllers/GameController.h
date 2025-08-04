#pragma once
#include "../models/GameModel.h"
#include "../views/GameView.h"
#include "../managers/UndoManager.h"
#include <memory>
#include <string>

class GameController {
public:
    GameController();
    void startGame(const std::string& levelConfigPath, cocos2d::Layer* parent);
    void undoLast();

private:
    std::unique_ptr<GameModel> _gameModel;
    GameView* _gameView = nullptr;
    UndoManager _undoManager;

    void tryReplaceTopWith(std::shared_ptr<CardModel> clickedCard, class CardView* clickedView);
    // 用于追踪 view，简化示例，用 id->view 映射
    std::unordered_map<int, class CardView*> _modelViewMap;
};
