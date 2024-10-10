#include <graphics.h>
#include "Knight.h"
#include "define.h"

void load_game_resourses(){
    atlas_knight_idle_left.load_from_file(_T("images/Idle/%d.PNG"), 9);
    atlas_knight_idle_right.load_from_file(_T("images/IdleR/%d.PNG"), 9);
}

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
