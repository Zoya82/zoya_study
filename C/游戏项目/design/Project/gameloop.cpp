#include <easyx.h>
#include "gameloop.h"
#include "scene.h"

void gameLoop(struct scene* s, int fps)
{
    timeBeginPeriod(1);                                  // 开始时间、结束时间、频率F

    LARGE_INTEGER startCount, endCount, F;               // 获取频率F

    QueryPerformanceFrequency(&F);

    bool isLoopOver = false;                             // 循环结束

    BeginBatchDraw();
    while (!isLoopOver)                                  // 修改此处的循环终止条件
    {
        QueryPerformanceCounter(&startCount);             // 获取起始计数
        cleardevice();                                   // 清空窗体
        s->draw(s);                                      // 1. 绘制画面
        s->update(s);                                    // 2. 更新数据

        if (s->isQuit(s))                                // 3. 是否结束
            break;

        QueryPerformanceCounter(&endCount);               // 获取结束计数

        long long elapse = (endCount.QuadPart - startCount.QuadPart)        // 计算时差
            / F.QuadPart * 1000000;


        while (elapse < 1000000 / fps)                    // 注意这里的单位是微秒
        {
            Sleep(1);

            ExMessage msg;                                // 4. 处理消息
            bool isOk = peekmessage(&msg, EX_MOUSE|EX_KEY);
            if (isOk == true)
            {
                s->control(s, &msg);
            }

            QueryPerformanceCounter(&endCount);           // 重新获取结束时间

            elapse = (endCount.QuadPart - startCount.QuadPart)         // 更新时差
                * 1000000 / F.QuadPart;
        }

        FlushBatchDraw();                                 // 绘制画面

        // 判断游戏是否结束
        isLoopOver = s->isQuit(s);
    }
    EndBatchDraw();
    timeEndPeriod(1);  // 移动到循环外部
}