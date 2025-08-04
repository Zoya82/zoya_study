#pragma once
#include <vector>
#include <memory>
#include "CardModel.h"

/**
 * @brief ��Ϸ����ʱ����״̬
 */
class GameModel {
public:
    void addPlayfieldCard(std::shared_ptr<CardModel> card);
    void setTopTrayCard(std::shared_ptr<CardModel> card);
    std::shared_ptr<CardModel> getTopTrayCard() const;
    const std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() const;

private:
    std::vector<std::shared_ptr<CardModel>> _playfieldCards;
    std::shared_ptr<CardModel> _trayTopCard; // ���ƶ���
};
