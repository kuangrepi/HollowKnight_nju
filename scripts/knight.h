//
// Created by yzzhhy on 24-10-10.
//

#ifndef HOLLOWKNIGHT_DEMO_KNIGHT_H
#define HOLLOWKNIGHT_DEMO_KNIGHT_H


#include "player.h"

class knight:public Player
{
public:
    knight() = default;
    ~knight() = default;

    void on_update(int delta)
    {
        std::cout << "小骑士正在更新" << std::endl;

    }
private:
};


#endif //HOLLOWKNIGHT_DEMO_KNIGHT_H
