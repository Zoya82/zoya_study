#include "Logger.h"
#include "cocos2d.h"

void Logger::info(const std::string& msg) {
    cocos2d::log("[INFO] %s", msg.c_str());
}

void Logger::error(const std::string& msg) {
    cocos2d::log("[ERROR] %s", msg.c_str());
}
