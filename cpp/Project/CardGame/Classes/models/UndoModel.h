#pragma once
#include <functional>

/**
 * @brief 单条可撤销行为数据（用在更高层复合）
 */
struct UndoModel {
    std::function<void()> undoAction;
    std::function<void()> redoAction;
};
