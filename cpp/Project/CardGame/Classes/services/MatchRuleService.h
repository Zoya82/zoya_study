#pragma once
#include "models/CardModel.h"

class MatchRuleService {
public:
    // �ж� a �Ƿ���� b ƥ�䣨������1��
    static bool canMatch(const CardModel& a, const CardModel& b);
};
