#pragma once
#include <functional>

/**
 * @brief �����ɳ�����Ϊ���ݣ����ڸ��߲㸴�ϣ�
 */
struct UndoModel {
    std::function<void()> undoAction;
    std::function<void()> redoAction;
};
