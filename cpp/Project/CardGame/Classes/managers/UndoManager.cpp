#include "UndoManager.h"

void UndoManager::record(const UndoRecord& record) {
    // 如果当前在中间，丢弃后面的 redo 记录
    if (_currentIndex + 1 < static_cast<int>(_stack.size())) {
        _stack.erase(_stack.begin() + _currentIndex + 1, _stack.end());
    }
    _stack.push_back(record);
    _currentIndex = static_cast<int>(_stack.size()) - 1;
}

void UndoManager::undo() {
    if (_currentIndex < 0) return;
    _stack[_currentIndex].undoAction();
    _currentIndex--;
}

void UndoManager::redo() {
    if (_currentIndex + 1 >= static_cast<int>(_stack.size())) return;
    _currentIndex++;
    _stack[_currentIndex].redoAction();
}
