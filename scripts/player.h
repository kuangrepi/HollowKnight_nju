//
// Created by yzzhhy on 24-10-10.
//

#ifndef HOLLOWKNIGHT_DEMO_PLAYER_H
#define HOLLOWKNIGHT_DEMO_PLAYER_H

#include "Camera.h"
#include <graphics.h>
#include <iostream>

class Player {
public:
    Player() = default;
    ~Player() = default;

    virtual void on_update(int delta)
    {
    }

    virtual void on_draw(const Camera & camera)
    {
    }

    virtual void on_input(const ExMessage& msg)
    {

    }




private:
};



#endif //HOLLOWKNIGHT_DEMO_PLAYER_H
