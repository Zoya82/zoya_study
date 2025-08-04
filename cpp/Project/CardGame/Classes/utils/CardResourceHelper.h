#pragma once
#include <string>
#include "../models/CardDefs.h" // ����ö��

class CardResourceHelper {
public:
    // ���ص���ͼƬ�������� "res/number/small_red_A.png"��
    static std::string getNumberSpritePath(CardFaceType face, CardSuitType suit, bool small = true);

    // ���ػ�ɫͼƬ�������� "res/suits/heart.png"��
    static std::string getSuitSpritePath(CardSuitType suit);

    // ����/�װ�
    static std::string getCardBackgroundPath();
};
