//
// Created by yzzhhy on 24-10-10.
//

#ifndef HOLLOWKNIGHT_DEMO_PLAYER_H
#define HOLLOWKNIGHT_DEMO_PLAYER_H

#include "Camera.h"
#include <graphics.h>
#include <iostream>
#include <unordered_map>
#include "collision_box.h"
#include "animation.h"
#include "timer.h"
#include "StateMachine"

class Player
{
public:
    Player();
    ~Player();

    virtual void on_update(int delta);

    virtual void on_draw(const Camera& camera);

    virtual void on_input(const ExMessage& msg) {

    }

    virtual void on_hurt() {

    }

    void decrease_hp() {
        if (!is_invulnerable) {
            hp--;
            is_invulnerable = true;
            timer_invulnerable_status.restart();
            timer_invulnerable_blink.restart();
        }
        std::cout << "hp: " << hp << std::endl;
    }

    void set_position(float x, float y) {
        position.x = x;
        position.y = y;
    }

protected:
    const float FLOOR_Y = 620; // 地板的竖直方向坐标
    const float GRAVITY = 980 * 2; // 重力大小
    int hp = 10; // 角色生命值
    Vector2 position; // 角色脚底位置
    Vector2 velocity; // 角色速度
    float logic_height = 0; // 角色的逻辑高度
    bool is_facing_left = true; // 当前角色是否朝向左
    StateMachine state_machine;
    bool enable_gravity = true; // 启用重力模拟
    bool is_invulnerable = false; // 当前是否无敌
    Timer timer_invulnerable_blink; // 无敌闪烁状态定时器
    Timer timer_invulnerable_status; // 无敌状态定时器
    bool is_blink_invisible = false; // 当前是否处于闪烁的不可见帧
    CollisionBox* hit_box = nullptr; // 攻击碰撞箱
    CollisionBox* hurt_box = nullptr; // 受击碰撞箱
    std::unordered_map<std::string, Animation> animation_pool; // 角色动画池

};

#endif //HOLLOWKNIGHT_DEMO_PLAYER_H
