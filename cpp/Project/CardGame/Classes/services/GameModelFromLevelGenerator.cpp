#include "GameModelFromLevelGenerator.h"
#include "../models/CardModel.h"
#include "../models/GameModel.h"
#include "../models/CardDefs.h"

std::unique_ptr<GameModel> GameModelFromLevelGenerator::generate(const LevelConfig& levelConfig) {
    auto gameModel = std::make_unique<GameModel>();
    int idCounter = 0;

    for (const auto& cfg : levelConfig.getPlayfield()) {
        auto face = static_cast<CardFaceType>(cfg.CardFace);
        auto suit = static_cast<CardSuitType>(cfg.CardSuit);
        auto card = std::make_shared<CardModel>(idCounter++, face, suit, cfg.Position);
        gameModel->addPlayfieldCard(card);
    }

    if (!levelConfig.getStack().empty()) {
        const auto& topCfg = levelConfig.getStack()[0];
        auto face = static_cast<CardFaceType>(topCfg.CardFace);
        auto suit = static_cast<CardSuitType>(topCfg.CardSuit);
        auto top = std::make_shared<CardModel>(idCounter++, face, suit, topCfg.Position);
        gameModel->setTopTrayCard(top);
    }
    return gameModel;
}
