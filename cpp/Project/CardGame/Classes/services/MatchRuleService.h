#pragma once
#include "models/CardModel.h"

class MatchRuleService {
public:
    // 判断 a 是否可与 b 匹配（点数差1）
    static bool canMatch(const CardModel& a, const CardModel& b);
};
