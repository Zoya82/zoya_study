#pragma once
#include "../models/CardModel.h"
#include "../views/CardView.h"
#include <functional>

class CardController {
public:
    using ClickCallback = std::function<void(std::shared_ptr<CardModel>, CardView*)>;
    CardController(std::shared_ptr<CardModel> model, CardView* view);
    void setClickCallback(const ClickCallback& cb);

private:
    std::shared_ptr<CardModel> _model;
    CardView* _view;
    ClickCallback _clickCallback;
};
