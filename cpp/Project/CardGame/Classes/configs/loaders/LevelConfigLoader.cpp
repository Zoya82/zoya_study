#include "LevelConfigLoader.h"
#include "../models/LevelConfig.h"
#include "cocos2d.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace cocos2d;

std::unique_ptr<LevelConfig> LevelConfigLoader::loadFromFile(const std::string& filepath) {
    auto config = std::make_unique<LevelConfig>();
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filepath);
    std::string content = FileUtils::getInstance()->getStringFromFile(fullPath);
    if (content.empty()) return nullptr;

    Document doc;
    doc.Parse(content.c_str());
    if (doc.HasParseError()) return nullptr;

    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        for (auto& item : doc["Playfield"].GetArray()) {
            CardPlacementConfig cfg{};
            if (item.HasMember("CardFace")) cfg.CardFace = item["CardFace"].GetInt();
            if (item.HasMember("CardSuit")) cfg.CardSuit = item["CardSuit"].GetInt();
            if (item.HasMember("Position")) {
                auto& pos = item["Position"];
                float x = pos.HasMember("x") ? pos["x"].GetFloat() : 0;
                float y = pos.HasMember("y") ? pos["y"].GetFloat() : 0;
                cfg.Position = Vec2(x, y);
            }
            config->addPlayfieldCard(cfg);
        }
    }
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        for (auto& item : doc["Stack"].GetArray()) {
            CardPlacementConfig cfg{};
            if (item.HasMember("CardFace")) cfg.CardFace = item["CardFace"].GetInt();
            if (item.HasMember("CardSuit")) cfg.CardSuit = item["CardSuit"].GetInt();
            if (item.HasMember("Position")) {
                auto& pos = item["Position"];
                float x = pos.HasMember("x") ? pos["x"].GetFloat() : 0;
                float y = pos.HasMember("y") ? pos["y"].GetFloat() : 0;
                cfg.Position = Vec2(x, y);
            }
            config->addStackCard(cfg);
        }
    }
    return config;
}
