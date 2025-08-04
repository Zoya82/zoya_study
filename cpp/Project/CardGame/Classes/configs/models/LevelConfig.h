#pragma once
#include <vector>
#include "cocos2d.h"

struct CardPlacementConfig {
    int CardFace;
    int CardSuit;
    cocos2d::Vec2 Position;
};

class LevelConfig {
public:
    const std::vector<CardPlacementConfig>& getPlayfield() const { return _playfield; }
    const std::vector<CardPlacementConfig>& getStack() const { return _stack; }
    void addPlayfieldCard(const CardPlacementConfig& cfg) { _playfield.push_back(cfg); }
    void addStackCard(const CardPlacementConfig& cfg) { _stack.push_back(cfg); }

private:
    std::vector<CardPlacementConfig> _playfield;
    std::vector<CardPlacementConfig> _stack;
};
