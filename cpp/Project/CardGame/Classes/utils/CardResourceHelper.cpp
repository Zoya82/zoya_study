#include "CardResourceHelper.h"

std::string CardResourceHelper::getNumberSpritePath(CardFaceType face, CardSuitType suit, bool small) {
    std::string sizePrefix = small ? "small_" : "big_";
    std::string color = (suit == CST_HEARTS || suit == CST_DIAMONDS) ? "red" : "black";

    std::string faceStr;
    switch (face) {
    case CFT_ACE: faceStr = "A"; break;
    case CFT_TWO: faceStr = "2"; break;
    case CFT_THREE: faceStr = "3"; break;
    case CFT_FOUR: faceStr = "4"; break;
    case CFT_FIVE: faceStr = "5"; break;
    case CFT_SIX: faceStr = "6"; break;
    case CFT_SEVEN: faceStr = "7"; break;
    case CFT_EIGHT: faceStr = "8"; break;
    case CFT_NINE: faceStr = "9"; break;
    case CFT_TEN: faceStr = "10"; break;
    case CFT_JACK: faceStr = "J"; break;
    case CFT_QUeen: faceStr = "Q"; break;
    case CFT_KING: faceStr = "K"; break;
    default: faceStr = "A"; break;
    }

    // АэИз "res/number/small_red_A.png"
    return "res/number/" + sizePrefix + color + "_" + faceStr + ".png";
}

std::string CardResourceHelper::getSuitSpritePath(CardSuitType suit) {
    switch (suit) {
    case CST_CLUBS: return "res/suits/club.png";
    case CST_DIAMONDS: return "res/suits/diamond.png";
    case CST_HEARTS: return "res/suits/heart.png";
    case CST_SPADES: return "res/suits/spade.png";
    default: return "";
    }
}

std::string CardResourceHelper::getCardBackgroundPath() {
    return "res/card_general.png";
}
