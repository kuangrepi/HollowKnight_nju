#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SceneManager.h"
#include "collision_manager.h"
#include "Knight.h"
#include "enemy.h"

#include <iostream>

extern SceneManager scene_manager;
extern IMAGE img_gamescene_background;

extern Knight* knight_1;
extern Enemy* enemy;

class Gamescene : public Scene
{
    Camera camera;

public:
    Gamescene() = default;

    ~Gamescene() = default;

    void on_enter() {
        knight_1 = new Knight();
        knight_1->set_position(600, 520);
        enemy = new Enemy();
        enemy->set_position(100, 120);
    }

    void on_exit() {
        delete knight_1;
        delete enemy;
    }

    void on_input(const ExMessage& msg) {
        knight_1->on_input(msg);
        if (enemy->is_on_debug) { enemy->on_input(msg); }
    }

    void on_update(int delta) {
        knight_1->on_update(delta);
        enemy->on_update(delta);
        CollisionManager* collision_manager = CollisionManager::instance();
        collision_manager->process_collision();
        if (knight_1->is_dead) {
            scene_manager.switch_to(SceneManager::SceneType::MenuScene);
            mciSendString(_T("stop Hornet"), NULL, 0, NULL);
            mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
            knight_1->hp = 10;
            enemy->hp = 20;
        }
    }

    void on_draw() {
        putimage(0, 0, &img_gamescene_background);

        knight_1->on_draw(camera);
        enemy->on_draw(camera);
        CollisionManager* collision_manager = CollisionManager::instance();
        //collision_manager->on_debug_draw();
    }

private:
};

#endif //GAMESCENE_H
