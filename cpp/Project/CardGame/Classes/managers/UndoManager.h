#pragma once
#include <vector>
#include <functional>

struct UndoRecord {
    std::function<void()> undoAction;
    std::function<void()> redoAction;
};

/**
 * @brief 负责记录和执行撤销/重做（非单例）
 */
class UndoManager {
public:
    void record(const UndoRecord& record);
    void undo();
    void redo();

private:
    std::vector<UndoRecord> _stack;
    int _currentIndex = -1; // 指向最后执行的位置
};
