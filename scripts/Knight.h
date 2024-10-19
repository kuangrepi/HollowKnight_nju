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
extern Atlas atlas_knight_jump_start_left;
extern Atlas atlas_knight_jump_start_right;
extern Atlas atlas_knight_jump_loop_left;
extern Atlas atlas_knight_jump_loop_right;
extern Atlas atlas_knight_jump_land_left;
extern Atlas atlas_knight_jump_land_right;
extern Atlas altas_knight_attack_left_1;
extern Atlas altas_knight_attack_right_1;
extern Atlas altas_knight_attack_left_effect_1;
extern Atlas altas_knight_attack_right_effect_1;
extern Atlas altas_knight_attack_left_up;
extern Atlas altas_knight_attack_right_up;
extern Atlas altas_knight_attack_left_effect_up;
extern Atlas altas_knight_attack_right_effect_up;
extern Atlas altas_knight_attack_left_down;
extern Atlas altas_knight_attack_right_down;
extern Atlas altas_knight_attack_left_effect_down;
extern Atlas altas_knight_attack_right_effect_down;
extern Atlas altas_knight_damage_left;
extern Atlas altas_knight_damage_right;
extern Atlas altas_knight_damage_effect;
extern Atlas altas_knight_death;

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
        if (start_jump <= 120 && velocity.y >= -0.1f) {
            if (start_jump == 1) velocity.y += jump_velocity;
            else velocity.y += jump_velocity / 25;
            start_jump++;
        }
    }

    void move_and_collide(int delta);

    bool game_over(){
        return is_dead;
    }
    Vector2 effect_position;
    Vector2 position_hurt_box; // 角色碰撞箱位置
    Vector2 position_hit_box; // 角色攻击箱位置

    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_knight_start_run_left;
    Animation animation_knight_start_run_right;
    Animation animation_run_left;
    Animation animation_run_right;
    Animation animation_jump_start_left;
    Animation animation_jump_start_right;
    Animation animation_jump_loop_left;
    Animation animation_jump_loop_right;
    Animation animation_jump_land_left;
    Animation animation_jump_land_right;
    Animation animation_attack_left_1;
    Animation animation_attack_right_1;
    Animation animation_attack_left_effect_1;
    Animation animation_attack_right_effect_1;
    Animation animation_attack_left_up;
    Animation animation_attack_right_up;
    Animation animation_attack_left_effect_up;
    Animation animation_attack_right_effect_up;
    Animation animation_attack_left_down;
    Animation animation_attack_right_down;
    Animation animation_attack_left_effect_down;
    Animation animation_attack_right_effect_down;
    Animation animation_damage_left;
    Animation animation_damage_right;
    Animation animation_damage_effect;
    Animation animation_death;

    Animation* current_animation = nullptr;
    Animation* effect_animation = nullptr;

    bool is_left_key_down = false;
    bool is_right_key_down = false;
    bool is_up_key_down = false;
    bool is_down_key_down = false;

    bool is_facing_right = true;
    bool effect_facing_right;

    bool is_jump = false;

    bool is_land = false;

    bool is_attack = false;
    bool normal_attack = false;
    bool up_attack = false;
    bool down_attack = false;
    bool is_damage = false;
    bool is_dead = false;
    Vector2 dead_position;

    int start_run = 0;
    int start_jump = 1;
    int damage = 1000;
    int attack = 1000;
    int attack_down = 10;

    const float gravity = 0.010f / FRAME;
    const float run_velocity = 8.0f / FRAME;
    const float jump_velocity = -22.0f / FRAME;
};

#endif //HOLLOWKNIGHT_DEMO_KNIGHT_H

