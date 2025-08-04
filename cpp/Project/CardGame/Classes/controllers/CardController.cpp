#include "CardController.h"

CardController::CardController(std::shared_ptr<CardModel> model, CardView* view)
    : _model(model), _view(view) {
    _view->setClickCallback([this](std::shared_ptr<CardModel> m) {
        if (_clickCallback) _clickCallback(_model, _view);
        });
}

void CardController::setClickCallback(const ClickCallback& cb) {
    _clickCallback = cb;
}
