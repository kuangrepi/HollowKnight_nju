#ifndef HOLLOWKNIGHT_DEMO_KNIGHT_H
#define HOLLOWKNIGHT_DEMO_KNIGHT_H

#include "player.h"
#include "Vector2.h"
#include "Animation.h"
#include "define.h"

extern Atlas atlas_knight_idle_left;
extern Atlas atlas_knight_idle_right;
extern Atlas atlas_knight_start_run_left;
extern Atlas atlas_knight_start_run_right;
extern Atlas atlas_knight_run_left;
extern Atlas atlas_knight_run_right;

class Knight : public Player
{
public:
    Knight();
    ~Knight() = default;

    void on_update(int delta) override;

    void on_input(const ExMessage& msg) override;

    void on_draw(const Camera& camera) override;

    void set_position(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void on_run(float distance) {
        position.x += distance;
    }

    void on_jump() {
        if(start_jump <= 120 && velocity.y >= -0.1f){
            if(start_jump == 1) velocity.y += jump_velocity;
            else velocity.y += jump_velocity / 25;
            start_jump++;
        }
    }

    void move_and_collide(int delta);

private:
    int hp = 10; // 角色生命值
    Vector2 position; // 角色脚底位置
    Vector2 position_hurt_box; // 角色碰撞箱位置
    Vector2 velocity; // 角色速度

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_knight_start_run_left;
    Animation animation_knight_start_run_right;
    Animation animation_run_left;
    Animation animation_run_right;

    Animation* current_animation = nullptr;

    bool is_left_key_down = false;
    bool is_right_key_down = false;

    bool is_facing_right = true;

    bool is_jump = false;

    int start_run = 0;
    int start_jump = 1;

    const float gravity = 0.005f / FRAME;
    const float run_velocity = 6.0f / FRAME;
    const float jump_velocity = -10.0f / FRAME;
};

#endif //HOLLOWKNIGHT_DEMO_KNIGHT_H

