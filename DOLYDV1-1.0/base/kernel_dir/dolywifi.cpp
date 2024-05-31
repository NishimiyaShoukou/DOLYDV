#include "dolywifi.h"
#include <iostream>
#include <cstdlib>

bool isWifiConnected() {
    // 执行iwgetid命令，并将结果重定向到null
    int result = system("iwgetid -r > /dev/null 2>&1");
    // system函数返回0表示命令执行成功，即WiFi已连接
    return result == 0;
}
