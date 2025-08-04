#pragma once
#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"
#include <memory>

/**
 * @brief 把静态关卡配置转换成运行时 GameModel
 */
class GameModelFromLevelGenerator {
public:
    static std::unique_ptr<GameModel> generate(const LevelConfig& levelConfig);
};
