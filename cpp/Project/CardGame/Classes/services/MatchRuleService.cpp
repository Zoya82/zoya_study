#include "MatchRuleService.h"
#include <cmath>

bool MatchRuleService::canMatch(const CardModel& a, const CardModel& b) {
    int faceA = static_cast<int>(a.getFace());
    int faceB = static_cast<int>(b.getFace());
    return std::abs(faceA - faceB) == 1;
}
