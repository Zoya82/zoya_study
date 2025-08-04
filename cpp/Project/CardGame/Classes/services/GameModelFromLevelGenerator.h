#pragma once
#include "models/GameModel.h"
#include "configs/models/LevelConfig.h"
#include <memory>

/**
 * @brief �Ѿ�̬�ؿ�����ת��������ʱ GameModel
 */
class GameModelFromLevelGenerator {
public:
    static std::unique_ptr<GameModel> generate(const LevelConfig& levelConfig);
};
