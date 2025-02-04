#include <graphics.h>
#include <windows.h>
#include "Knight.h"
#include "define.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "sword.h"
#include "barb.h"
#include "enemy.h"
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

IMAGE img_gamescene_background; //游戏背景图片
IMAGE img_menuscene_background;

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;

Knight* knight_1 = nullptr;
Enemy* enemy = nullptr;

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
    altas_knight_attack_left_effect_1.load_from_file(_T("images/Attack/Attack/1/0%d.PNG"), 3);
    altas_knight_attack_right_effect_1.load_from_file(_T("images/AttackR/Attack/1/0%d.PNG"), 3);
    altas_knight_attack_left_up.load_from_file(_T("images/Attack/AttackUp/%d.PNG"), 5);
    altas_knight_attack_right_up.load_from_file(_T("images/AttackR/AttackUp/%d.PNG"), 5);
    altas_knight_attack_left_effect_up.load_from_file(_T("images/Attack/AttackUp/0%d.PNG"), 3);
    altas_knight_attack_right_effect_up.load_from_file(_T("images/AttackR/AttackUp/0%d.PNG"), 3);
    altas_knight_attack_left_down.load_from_file(_T("images/Attack/AttackDown/%d.PNG"), 5);
    altas_knight_attack_right_down.load_from_file(_T("images/AttackR/AttackDown/%d.PNG"), 5);
    altas_knight_attack_left_effect_down.load_from_file(_T("images/Attack/AttackDown/0%d.PNG"), 3);
    altas_knight_attack_right_effect_down.load_from_file(_T("images/AttackR/AttackDown/0%d.PNG"), 3);
    altas_knight_damage_left.load_from_file(_T("images/Damage/%d.PNG"), 7);
    altas_knight_damage_right.load_from_file(_T("images/DamageR/%d.PNG"), 7);
    altas_knight_damage_effect.load_from_file(_T("images/DamageR/0%d.PNG"), 4);
    altas_knight_death.load_from_file(_T("images/Death/%d.PNG"), 11);
    // 黄蜂女道具
    atlas_sword_left.load_from_file(_T("images/enemy/sword_left/%d.PNG"), 3);
    atlas_sword_right.load_from_file(_T("images/enemy/sword_right/%d.PNG"), 3);
    atlas_barb_loose.load_from_file(_T("images/enemy/barb_loose/%d.PNG"), 5);
    atlas_barb_break.load_from_file(_T("images/enemy/barb_break/%d.PNG"), 3);
    // 黄蜂女动画
    atlas_silk.load_from_file(_T("images/enemy/silk/%d.PNG"), 9);
    atlas_aim_left.load_from_file(_T("images/enemy/aim_left/%d.PNG"), 9);
    atlas_aim_right.load_from_file(_T("images/enemy/aim_right/%d.PNG"), 9);
    atlas_dash_in_air_left.load_from_file(_T("images/enemy/dash_in_air_left/%d.PNG"), 2);
    atlas_dash_in_air_right.load_from_file(_T("images/enemy/dash_in_air_right/%d.PNG"), 2);
    atlas_dash_on_floor_left.load_from_file(_T("images/enemy/dash_on_floor_left/%d.PNG"), 2);
    atlas_dash_on_floor_right.load_from_file(_T("images/enemy/dash_on_floor_right/%d.PNG"), 2);
    atlas_fall_left.load_from_file(_T("images/enemy/fall_left/%d.PNG"), 4);
    atlas_fall_right.load_from_file(_T("images/enemy/fall_right/%d.PNG"), 4);
    atlas_idle_left.load_from_file(_T("images/enemy/idle_left/%d.PNG"), 6);
    atlas_idle_right.load_from_file(_T("images/enemy/idle_right/%d.PNG"), 6);
    atlas_jump_left.load_from_file(_T("images/enemy/jump_left/%d.PNG"), 8);
    atlas_jump_right.load_from_file(_T("images/enemy/jump_right/%d.PNG"), 8);
    atlas_run_left.load_from_file(_T("images/enemy/run_left/%d.PNG"), 8);
    atlas_run_right.load_from_file(_T("images/enemy/run_right/%d.PNG"), 8);
    atlas_squat_left.load_from_file(_T("images/enemy/squat_left/%d.PNG"), 10);
    atlas_squat_right.load_from_file(_T("images/enemy/squat_right/%d.PNG"), 10);
    atlas_throw_barb_left.load_from_file(_T("images/enemy/throw_barb_left/%d.PNG"), 8);
    atlas_throw_barb_right.load_from_file(_T("images/enemy/throw_barb_right/%d.PNG"), 8);
    atlas_throw_sword_left.load_from_file(_T("images/enemy/throw_sword_left/%d.PNG"), 16);
    atlas_throw_sword_right.load_from_file(_T("images/enemy/throw_sword_right/%d.PNG"), 16);
    atlas_throw_silk_left.load_from_file(_T("images/enemy/throw_silk_left/%d.PNG"), 17);
    atlas_throw_silk_right.load_from_file(_T("images/enemy/throw_silk_right/%d.PNG"), 17);
    atlas_vfx_dash_in_air_left.load_from_file(_T("images/enemy/vfx_dash_in_air_left/%d.PNG"), 5);
    atlas_vfx_dash_in_air_right.load_from_file(_T("images/enemy/vfx_dash_in_air_right/%d.PNG"), 5);
    atlas_vfx_dash_on_floor_left.load_from_file(_T("images/enemy/vfx_dash_on_floor_left/%d.PNG"), 6);
    atlas_vfx_dash_on_floor_right.load_from_file(_T("images/enemy/vfx_dash_on_floor_right/%d.PNG"), 6);

    loadimage(&img_gamescene_background, _T("images/background.png"));
    loadimage(&img_menuscene_background, _T("images/menu.png"));

    atlas_blood_decrease.load_from_file(_T("images/UI/Blood/Damage/%d.PNG"), 7);
    atlas_blood_normal.load_from_file(_T("images/UI/Blood/tmp/%d.PNG"), 6);
}

int main() {
    load_game_resourses();
    initgraph(1280, 720);
    setbkmode(TRANSPARENT);
    settextcolor(RGB(255, 255, 255));

    settextstyle(40, 0, _T("黑体"));

    mciSendString("open audio/Player/player_damage.mp3 alias player_damage", NULL, 0, NULL);
    mciSendString("open audio/Player/sword_1.mp3 alias sword_1", NULL, 0, NULL);
    mciSendString("open audio/Player/sword_2.mp3 alias sword_2", NULL, 0, NULL);
    mciSendString("open audio/Player/sword_hit.mp3 alias sword_hit", NULL, 0, NULL);
    mciSendString("open audio/Player/sword_up.mp3 alias sword_up", NULL, 0, NULL);
    mciSendString("open audio/barb_break.mp3 alias barb_break", NULL, 0, NULL);
    mciSendString("open audio/bgm.mp3 alias bgm", NULL, 0, NULL);
    mciSendString("open audio/bullet_time.mp3 alias bullet_time", NULL, 0, NULL);
    mciSendString("open audio/enemy_dash.mp3 alias enemy_dash", NULL, 0, NULL);
    mciSendString("open audio/enemy_hurt_1.mp3 alias enemy_hurt_1", NULL, 0, NULL);
    mciSendString("open audio/enemy_hurt_2.mp3 alias enemy_hurt_2", NULL, 0, NULL);
    mciSendString("open audio/enemy_hurt_3.mp3 alias enemy_hurt_3", NULL, 0, NULL);
    mciSendString("open audio/enemy_run.mp3 alias enemy_run", NULL, 0, NULL);
    mciSendString("open audio/enemy_throw_barbs.mp3 alias enemy_throw_barbs", NULL, 0, NULL);
    mciSendString("open audio/enemy_throw_silk.mp3 alias enemy_throw_silk", NULL, 0, NULL);
    mciSendString("open audio/enemy_throw_sword.mp3 alias enemy_throw_sword", NULL, 0, NULL);
    mciSendString("open audio/Hornet.mp3 alias Hornet", NULL, 0, NULL);

    bool running = true;

    ExMessage msg;

    BeginBatchDraw();

    game_scene = new Gamescene();
    menu_scene = new Menuscene();

    scene_manager.set_current_scene(menu_scene);
    mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

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
        if (delta_time < 1.0 / FRAME * 2) {
            Sleep(static_cast<DWORD>((1.0 / FRAME * 2 - delta_time) * 1000));
        }
    }

    EndBatchDraw();
    return 0;
}
