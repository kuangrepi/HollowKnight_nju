//
// Created by yzzhhy on 24-10-10.
//

#ifndef HOLLOWKNIGHT_DEMO_HORNET_H
#define HOLLOWKNIGHT_DEMO_HORNET_H

#include "player.h"
#include "Vector2.h"
#include "Animation.h"
#include "define.h"

extern Atlas atlas_hornet_idle_left;
extern Atlas atlas_hornet_idle_right;
extern Atlas atlas_hornet_run_left;
extern Atlas atlas_hornet_run_right;

class Hornet:public Player
{
public:
    Hornet(){
        animation_idle_left.set_atlas(&atlas_hornet_idle_left);
        animation_idle_right.set_atlas(&atlas_hornet_idle_right);
        animation_run_left.set_atlas(&atlas_hornet_run_left);
        animation_run_right.set_atlas(&atlas_hornet_run_right);

        animation_idle_left.set_interval(INTERVAL);
        animation_idle_right.set_interval(INTERVAL);
        animation_run_left.set_interval(INTERVAL*6);
        animation_run_right.set_interval(INTERVAL*6);
    }
    ~Hornet() = default;

    void on_update(int delta) override
    {
        std::cout << "大黄蜂正在更新" << std::endl;
        int direction = is_right_key_down - is_left_key_down;
        if(direction != 0){
            is_facing_right = direction > 0;
            current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
            float distance = direction * run_velocity * delta;
            on_run(distance);
        }
        else
            current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        current_animation->on_update(delta);
    }

    void on_input(const ExMessage& msg) override{
        switch (msg.message) {
            case WM_KEYDOWN:
                switch (msg.vkcode) {
                    case 0x4E: // N
                        is_left_key_down = true;
                        break;
                    case 0x4D: // M
                        is_right_key_down = true;
                        break;
                }
                break;
            case WM_KEYUP:
                switch (msg.vkcode) {
                    case 0x4E: // N
                        is_left_key_down = false;
                        break;
                    case 0x4D: // M
                        is_right_key_down = false;
                        break;
                }
                break;
            default:
                break;
        }
    }

    void on_draw(const Camera& camera) override{
        current_animation->on_draw((int)position.x, (int)position.y);
    }



    void set_position(float x, float y){
        position.x = x;
        position.y = y;
    }

    void on_run(float distance){
        position.x += distance;
    }


private:
    Vector2 position;
    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_run_left;
    Animation animation_run_right;

    Animation* current_animation = nullptr;

    bool is_left_key_down = false;
    bool is_right_key_down = false;

    bool is_facing_right = true;

    const float run_velocity = 0.15f;
};


#endif //HOLLOWKNIGHT_DEMO_HORNET_H
