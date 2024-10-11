//
// Created by oyster on 24-10-10.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SceneManager.h"

#include <iostream>

extern SceneManager scene_manager;
extern IMAGE img_gamescene_background;

class Gamescene : public Scene{
public:
    Gamescene() = default;
    ~Gamescene() = default;

    void on_enter() {

    }

    void on_exit() {

    }

    void on_input(const ExMessage& msg) {

    }

    void on_update() {

    }

    void on_draw() {
        putimage(0, 0, &img_gamescene_background);
    }

private:
};



#endif //GAMESCENE_H
