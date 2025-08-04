#pragma once
#include <vector>
#include <functional>

struct UndoRecord {
    std::function<void()> undoAction;
    std::function<void()> redoAction;
};

/**
 * @brief �����¼��ִ�г���/�������ǵ�����
 */
class UndoManager {
public:
    void record(const UndoRecord& record);
    void undo();
    void redo();

private:
    std::vector<UndoRecord> _stack;
    int _currentIndex = -1; // ָ�����ִ�е�λ��
};
