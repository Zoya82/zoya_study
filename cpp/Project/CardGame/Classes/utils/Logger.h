#pragma once
#include <string>

/**
 * @brief ������־���ߣ����滻Ϊ�����ӵ���־��ܣ�
 */
class Logger {
public:
    static void info(const std::string& msg);
    static void error(const std::string& msg);
};
