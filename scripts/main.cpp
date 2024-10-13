#include <graphics.h>
#include "Knight.h"
#include "define.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "sword.h"
#include "barb.h"
#include "enemy.h"

IMAGE img_gamescene_background;         //游戏背景图片

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;

Knight* knight_1 = nullptr;

SceneManager scene_manager;

void load_game_resourses() {
    // 小骑士资源
    atlas_knight_idle_left.load_from_file(_T("images/Idle/%d.PNG"), 9);
    atlas_knight_idle_right.load_from_file(_T("images/IdleR/%d.PNG"), 9);
    atlas_knight_start_run_left.load_from_file(_T("images/Start_run/%d.PNG"), 6);
    atlas_knight_start_run_right.load_from_file(_T("images/Start_runR/%d.PNG"), 6);
    atlas_knight_run_left.load_from_file(_T("images/Walk/%d.PNG"), 5);
    atlas_knight_run_right.load_from_file(_T("images/WalkR/%d.PNG"), 5);
    atlas_knight_jump_start_left.load_from_file(_T("images/Jump/Start/%d.PNG"), 12);
    atlas_knight_jump_start_right.load_from_file(_T("images/JumpR/Start/%d.PNG"), 12);
    atlas_knight_jump_loop_left.load_from_file(_T("images/Jump/Loop/%d.PNG"), 3);
    atlas_knight_jump_loop_right.load_from_file(_T("images/JumpR/Loop/%d.PNG"), 3);
    atlas_knight_jump_land_left.load_from_file(_T("images/Jump/Land/%d.PNG"), 3);
    atlas_knight_jump_land_right.load_from_file(_T("images/JumpR/Land/%d.PNG"), 3);
    altas_knight_attack_left_1.load_from_file(_T("images/Attack/Attack/1/%d.PNG"), 5);
    altas_knight_attack_right_1.load_from_file(_T("images/AttackR/Attack/1/%d.PNG"), 5);
    altas_knight_attack_left_effect_1.load_from_file(_T("images/Attack/Attack/1/0%d.PNG"), 2);
    altas_knight_attack_right_effect_1.load_from_file(_T("images/AttackR/Attack/1/0%d.PNG"), 2);
    // 黄蜂女道具
    atlas_sword.load_from_file(_T("images/enemy/sword/%d.PNG"), 3);
    atlas_barb_loose.load_from_file(_T("images/enemy/barb_loose/%d.PNG"), 5);
    atlas_barb_break.load_from_file(_T("images/enemy/barb_break/%d.PNG"), 3);
    // 黄蜂女动画
    atlas_silk.load_from_file(_T("images/enemy/silk/%d.PNG"), 3);
    atlas_aim_left.load_from_file(_T("images/enemy/aim_left/%d.PNG"), 3);
    atlas_aim_right.load_from_file(_T("images/enemy/aim_right/%d.PNG"), 3);
    atlas_dash_in_air_left.load_from_file(_T("images/enemy/dash_in_air_left/%d.PNG"), 3);
    atlas_dash_in_air_right.load_from_file(_T("images/enemy/dash_in_air_right/%d.PNG"), 3);
    atlas_dash_on_floor_left.load_from_file(_T("images/enemy/dash_on_floor_left/%d.PNG"), 3);
    atlas_dash_on_floor_right.load_from_file(_T("images/enemy/dash_on_floor_right/%d.PNG"), 3);
    atlas_fall_left.load_from_file(_T("images/enemy/fall_left/%d.PNG"), 3);
    atlas_fall_right.load_from_file(_T("images/enemy/fall_right/%d.PNG"), 3);
    atlas_idle_left.load_from_file(_T("images/enemy/idle_left/%d.PNG"), 3);
    atlas_idle_right.load_from_file(_T("images/enemy/idle_right/%d.PNG"), 3);
    atlas_jump_left.load_from_file(_T("images/enemy/jump_left/%d.PNG"), 3);
    atlas_jump_right.load_from_file(_T("images/enemy/jump_right/%d.PNG"), 3);
    atlas_run_left.load_from_file(_T("images/enemy/run_left/%d.PNG"), 3);
    atlas_run_right.load_from_file(_T("images/enemy/run_right/%d.PNG"), 3);
    atlas_squat_left.load_from_file(_T("images/enemy/squat_left/%d.PNG"), 3);
    atlas_squat_right.load_from_file(_T("images/enemy/squat_right/%d.PNG"), 3);
    atlas_throw_barb_left.load_from_file(_T("images/enemy/throw_barb_left/%d.PNG"), 3);
    atlas_throw_barb_right.load_from_file(_T("images/enemy/throw_barb_right/%d.PNG"), 3);
    atlas_throw_sword_left.load_from_file(_T("images/enemy/throw_sword_left/%d.PNG"), 3);
    atlas_throw_sword_right.load_from_file(_T("images/enemy/throw_sword_right/%d.PNG"), 3);
    atlas_throw_silk_left.load_from_file(_T("images/enemy/throw_silk_left/%d.PNG"), 3);
    atlas_throw_silk_right.load_from_file(_T("images/enemy/throw_silk_right/%d.PNG"), 3);
    atlas_vfx_dash_in_air_left.load_from_file(_T("images/enemy/vfx_dash_in_air_left/%d.PNG"), 3);
    atlas_vfx_dash_in_air_right.load_from_file(_T("images/enemy/vfx_dash_in_air_right/%d.PNG"), 3);

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
