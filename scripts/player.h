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
#include "state_machine.h"

class Player
{
public:
    Player();
    ~Player();

    virtual void on_update(int delta);

    virtual void on_draw(const Camera& camera);

    virtual void on_input(const ExMessage& msg);

    virtual void on_hurt();

    void decrease_hp();

    int get_hp() const {
        return hp;
    }

    void set_position(float x, float y) {
        position.x = x;
        position.y = y;
    }

    const Vector2& get_position() const {
        return position;
    }

    void set_velocity(float x, float y) {
        velocity.x = x;
        velocity.y = y;
    }

    const Vector2& get_velocity() const {
        return velocity;
    }

    void set_gravity_enabled(bool flag) {
        enable_gravity = flag;
    }

    CollisionBox* get_hit_box() const {
        return hit_box;
    }

    CollisionBox* get_hurt_box() const {
        return hurt_box;
    }

    bool is_on_floor() const {
        return position.y >= FLOOR_Y;
    }

    void make_invulnerable() {
        is_invulnerable = true;
        timer_invulnerable_status.restart();
    }

    void set_animation(Animation* animation);

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
    Animation* current_animation = nullptr; // 当前动画
    std::unordered_map<std::string, Animation> animation_pool; // 角色动画池



};

#endif //HOLLOWKNIGHT_DEMO_PLAYER_H
