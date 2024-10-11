//
// Created by oyster on 24-10-11.
//

#ifndef MENUSCENE_H
#define MENUSCENE_H



#include "Scene.h"
#include "SceneManager.h"

#include <iostream>

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

    }

    void on_update(int delta) {

    }

    void on_draw() {

    }

private:
};



#endif //MENUSCENE_H
