#pragma once
//#include "LevelConfig.h"
#include "configs/models/LevelConfig.h"
#include <string>
#include <memory>

class LevelConfigLoader {
public:
    static std::unique_ptr<LevelConfig> loadFromFile(const std::string& filepath);
};
