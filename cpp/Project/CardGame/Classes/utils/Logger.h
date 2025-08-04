#pragma once
#include <string>

/**
 * @brief 简易日志工具（可替换为更复杂的日志框架）
 */
class Logger {
public:
    static void info(const std::string& msg);
    static void error(const std::string& msg);
};
