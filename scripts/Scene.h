//
// Created by oyster on 24-10-10.
//

#ifndef SCENE_H
#define SCENE_H

#include <graphics.h>

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter() {}
    virtual void on_exit() {}
    virtual void on_draw() {}
    virtual void on_input(const ExMessage& msg) {}
    virtual void on_update() {}

private:
};



#endif //SCENE_H
