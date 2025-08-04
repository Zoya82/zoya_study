#pragma once
#include <string>
#include "../models/CardDefs.h" // 包含枚举

class CardResourceHelper {
public:
    // 返回点数图片名（比如 "res/number/small_red_A.png"）
    static std::string getNumberSpritePath(CardFaceType face, CardSuitType suit, bool small = true);

    // 返回花色图片名（比如 "res/suits/heart.png"）
    static std::string getSuitSpritePath(CardSuitType suit);

    // 卡背/底板
    static std::string getCardBackgroundPath();
};
