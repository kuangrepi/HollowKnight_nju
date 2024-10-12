#include <graphics.h>
#include "Knight.h"
#include "define.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SceneManager.h"

IMAGE img_gamescene_background;         //游戏背景图片

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;

Knight* knight_1 = nullptr;

SceneManager scene_manager;

void load_game_resourses() {
    // 小骑士资源
    atlas_knight_idle_left.load_from_file(_T("images/Idle/%d.PNG"), 9);
    atlas_knight_idle_right.load_from_file(_T("images/IdleR/%d.PNG"), 9);
    atlas_knight_start_run_left.load_from_file(_T("images/Walk/%d.PNG"), 11);
    atlas_knight_start_run_right.load_from_file(_T("images/WalkR/%d.PNG"), 11);
    atlas_knight_run_left.load_from_file(_T("images/Walk/%d.PNG"), 5);
    atlas_knight_run_right.load_from_file(_T("images/WalkR/%d.PNG"), 5);
    //
    loadimage(&img_gamescene_background, _T("images/background.png"));
}

int main() {
    load_game_resourses();
    initgraph(1280, 720);

    bool running = true;

    ExMessage msg;

    BeginBatchDraw();

    game_scene = new Gamescene();
    menu_scene = new Menuscene();

    scene_manager.set_current_scene(game_scene);

    LARGE_INTEGER frequency;
    LARGE_INTEGER start_time, end_time;
    QueryPerformanceFrequency(&frequency);

    while (running) {
        QueryPerformanceCounter(&start_time);

        while (peekmessage(&msg)) {
            scene_manager.on_input(msg);
        }

        scene_manager.on_update(FRAME);

        cleardevice();
        scene_manager.on_draw();
        FlushBatchDraw();

        QueryPerformanceCounter(&end_time);
        double delta_time = static_cast<double>(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
        if (delta_time < 1.0 / FRAME) {
            Sleep(static_cast<DWORD>((1.0 / FRAME - delta_time) * 1000));
        }
    }

    EndBatchDraw();
    return 0;
}

