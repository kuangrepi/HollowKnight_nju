#include <graphics.h>
#include "define.h"

int main()
{
    initgraph(1280, 720);

    bool running = true;

    ExMessage msg;

    BeginBatchDraw();

    while (running){
        DWORD start_time = GetTickCount();

        while (peekmessage(&msg)){

        }

        cleardevice();
        FlushBatchDraw();

        DWORD end_time = GetTickCount();
        DWORD delte_time = end_time - start_time;
        if (delte_time < 1000 / FRAME){
            Sleep(1000 / FRAME - delte_time);
        }
    }

    EndBatchDraw();
    return 0;
}
