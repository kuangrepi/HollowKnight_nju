//
// Created by oyster on 24-10-11.
//

#ifndef MENUSCENE_H
#define MENUSCENE_H



#include "Scene.h"
#include "SceneManager.h"

#include <iostream>

extern IMAGE img_menuscene_background;
extern SceneManager scene_manager;

class Menuscene : public Scene{
public:
    Menuscene() = default;
    ~Menuscene() = default;

    void on_enter() {

    }

    void on_exit() {

    }

    void on_input(const ExMessage& msg) {
        if(msg.message == WM_KEYDOWN) {
            scene_manager.switch_to(SceneManager::SceneType::GameScene);
        }
    }

    void on_update(int delta) {

    }

    void on_draw() {
        putimage(0, 0, &img_menuscene_background);
        outtextxy(670, 550, _T("按任意键开始游戏"));
    }

private:
};



#endif //MENUSCENE_H
