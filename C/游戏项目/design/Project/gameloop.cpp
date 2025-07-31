#include <easyx.h>
#include "gameloop.h"
#include "scene.h"

void gameLoop(struct scene* s, int fps)
{
    timeBeginPeriod(1);                                  // ��ʼʱ�䡢����ʱ�䡢Ƶ��F

    LARGE_INTEGER startCount, endCount, F;               // ��ȡƵ��F

    QueryPerformanceFrequency(&F);

    bool isLoopOver = false;                             // ѭ������

    BeginBatchDraw();
    while (!isLoopOver)                                  // �޸Ĵ˴���ѭ����ֹ����
    {
        QueryPerformanceCounter(&startCount);             // ��ȡ��ʼ����
        cleardevice();                                   // ��մ���
        s->draw(s);                                      // 1. ���ƻ���
        s->update(s);                                    // 2. ��������

        if (s->isQuit(s))                                // 3. �Ƿ����
            break;

        QueryPerformanceCounter(&endCount);               // ��ȡ��������

        long long elapse = (endCount.QuadPart - startCount.QuadPart)        // ����ʱ��
            / F.QuadPart * 1000000;


        while (elapse < 1000000 / fps)                    // ע������ĵ�λ��΢��
        {
            Sleep(1);

            ExMessage msg;                                // 4. ������Ϣ
            bool isOk = peekmessage(&msg, EX_MOUSE|EX_KEY);
            if (isOk == true)
            {
                s->control(s, &msg);
            }

            QueryPerformanceCounter(&endCount);           // ���»�ȡ����ʱ��

            elapse = (endCount.QuadPart - startCount.QuadPart)         // ����ʱ��
                * 1000000 / F.QuadPart;
        }

        FlushBatchDraw();                                 // ���ƻ���

        // �ж���Ϸ�Ƿ����
        isLoopOver = s->isQuit(s);
    }
    EndBatchDraw();
    timeEndPeriod(1);  // �ƶ���ѭ���ⲿ
}