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

class Menuscene : public Scene
{
public:
    Menuscene() = default;
    ~Menuscene() = default;

    void on_enter() {
    }

    void on_exit() {

    }

    void on_input(const ExMessage& msg) {
        if (msg.message == WM_KEYDOWN) {
            scene_manager.switch_to(SceneManager::SceneType::GameScene);
            mciSendString(_T("stop bgm"), NULL, 0, NULL);
            mciSendString("play Hornet repeat from 0", NULL, 0, NULL);
        }
    }

    void on_update(int delta) {

    }

    void on_draw() {
        putimage(0, 0, &img_menuscene_background);
        outtextxy(600, 550, _T("Press Any Key To Start"));
    }

private:
};

#endif //MENUSCENE_H
