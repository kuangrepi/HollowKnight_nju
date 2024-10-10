//
// Created by yzzhhy on 24-10-10.
//

#ifndef HOLLOWKNIGHT_DEMO_PLAYER_H
#define HOLLOWKNIGHT_DEMO_PLAYER_H

#include "Camera.h"
#include <graphics.h>
#include <iostream>
#include"Animation.h"

class Player {
public:
    Player()
    {
        current_animation = &animation_idle_right;
    }
    ~Player() = default;

    void set_position(float x, float y)
    {
        position.x = x, position.y = y;
    }



    virtual void on_update(int delta)
    {
        int direction = is_right_key_down - is_left_key_down;
        if (direction != 0)
        {
            is_facing_right = direction > 0;
            current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
        }
        else
        {
            current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        }
        current_animation->on_update(delta);

    }

    virtual void on_draw(const Camera & camera)
    {
        current_animation->on_draw((int)position.x, (int)position.y);
    }

    virtual void on_input(const ExMessage& msg)
    {
        switch (msg.message)
        {
            case WM_KEYDOWN:
            {
                switch (msg.vkcode)
                {
                    // 'A'
                    case 0x41:
                        is_left_key_down = true;
                        break;
                        // 'D'
                    case 0x44:
                        is_right_key_down = true;
                        break;
                }
                break;
            }
            case WM_KEYUP:
            {
                switch (msg.vkcode)
                {
                    // 'A'
                    case 0x41:
                        is_left_key_down = false;
                        break;

                        // 'D'
                    case 0x44:
                        is_right_key_down = false;
                        break;
                }
                break;
            }
            default:
                break;
        }
    }


protected:
    Vector2 position{};// 角色位置
    Animation animation_idle_left;// 朝向左的默认动画
    Animation animation_idle_right;// 朝向右的默认动画
    Animation animation_run_left;// 朝向左的奔跑动画
    Animation animation_run_right;// 朝向右的奔跑动画

    Animation* current_animation = nullptr;// 当前正在播放的动画

    bool is_left_key_down = false;// 向左移动按键是否按下
    bool is_right_key_down = false;// 向右移动按键是否按下
    bool is_facing_right = true;
};



#endif //HOLLOWKNIGHT_DEMO_PLAYER_H
