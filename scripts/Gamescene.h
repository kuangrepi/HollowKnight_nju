//
// Created by oyster on 24-10-10.
//

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SceneManager.h"
#include "Knight.h"
#include "Hornet.h"

#include <iostream>

extern SceneManager scene_manager;
extern IMAGE img_gamescene_background;

extern Knight* knight_1;
extern Hornet* hornet;

class Gamescene : public Scene{
    Camera camera;
public:
    Gamescene() = default;
    ~Gamescene() = default;

    void on_enter() {
        knight_1 = new Knight();
        knight_1->set_position(600, 520);
//        hornet=new Hornet();
//        hornet->set_position(100,520);
    }

    void on_exit() {

    }

    void on_input(const ExMessage& msg) {
        knight_1->on_input(msg);
//        hornet->on_input(msg);
    }

    void on_update(int delta) {
        knight_1->on_update(delta);
//        hornet->on_update(delta);
    }

    void on_draw() {
        putimage(0, 0, &img_gamescene_background);
        knight_1->on_draw(camera);
//        hornet->on_draw(camera);
    }

private:
};



#endif //GAMESCENE_H
