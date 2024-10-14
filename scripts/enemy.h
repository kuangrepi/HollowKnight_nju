#ifndef HOLLOWKNIGHT_DEMO_SCRIPTS_ENEMY_H_
#define HOLLOWKNIGHT_DEMO_SCRIPTS_ENEMY_H_

#include "player.h"
#include "barb.h"
#include "sword.h"
#include "state_machine.h"

extern Atlas atlas_silk;
extern Atlas atlas_aim_left;
extern Atlas atlas_aim_right;
extern Atlas atlas_dash_in_air_left;
extern Atlas atlas_dash_in_air_right;
extern Atlas atlas_dash_on_floor_left;
extern Atlas atlas_dash_on_floor_right;
extern Atlas atlas_fall_left;
extern Atlas atlas_fall_right;
extern Atlas atlas_idle_left;
extern Atlas atlas_idle_right;
extern Atlas atlas_jump_left;
extern Atlas atlas_jump_right;
extern Atlas atlas_run_left;
extern Atlas atlas_run_right;
extern Atlas atlas_squat_left;
extern Atlas atlas_squat_right;
extern Atlas atlas_throw_barb_left;
extern Atlas atlas_throw_barb_right;
extern Atlas atlas_throw_sword_left;
extern Atlas atlas_throw_sword_right;
extern Atlas atlas_throw_silk_left;
extern Atlas atlas_throw_silk_right;
extern Atlas atlas_vfx_dash_in_air_left;
extern Atlas atlas_vfx_dash_in_air_right;

#define floor 600

class Enemy : public Player
{
public:
    Enemy();
    ~Enemy();

    void on_update(int delta) override;
    void on_draw(const Camera& camera) override;
    void on_hurt() override {};
    void on_input(const ExMessage& msg);
    void set_facing_left(bool flag) {
        is_facing_left = flag;
    }

    bool get_facing_left() const {
        return is_facing_left;
    }

    void set_dashing_in_air(bool flag) {
        is_dashing_in_air = flag;
    }

    bool get_dashing_in_air() const {
        return is_dashing_in_air;
    }

    void set_dashing_on_floor(bool flag) {
        is_dashing_on_floor = flag;
    }

    bool get_dashing_on_floor() const {
        return is_dashing_on_floor;
    }

    void set_throwing_silk(bool flag) {
        is_throwing_silk = flag;
        collision_box_silk->set_enabled(flag);
    }

    bool get_throwing_silk() const {
        return is_throwing_silk;
    }

    void throw_barbs();
    void throw_sword();
    void on_dash();
    void on_throw_silk();

    //新增的一些函数
    void switch_state(const std::string& id);
    void set_animation(const std::string& id);

private:
    bool is_throwing_silk = false;
    bool is_dashing_in_air = false;
    bool is_dashing_on_floor = false;
    bool is_on_debug = true;

    // 动画资源
    Animation animation_silk;
    Animation animation_aim_left;
    Animation animation_aim_right;
    Animation animation_dash_in_air_left;
    Animation animation_dash_in_air_right;
    Animation animation_dash_on_floor_left;
    Animation animation_dash_on_floor_right;
    Animation animation_fall_left;
    Animation animation_fall_right;
    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_jump_left;
    Animation animation_jump_right;
    Animation animation_run_left;
    Animation animation_run_right;
    Animation animation_squat_left;
    Animation animation_squat_right;
    Animation animation_throw_barb_left;
    Animation animation_throw_barb_right;
    Animation animation_throw_sword_left;
    Animation animation_throw_sword_right;
    Animation animation_throw_silk_left;
    Animation animation_throw_silk_right;
    Animation animation_vfx_dash_in_air_left;
    Animation animation_vfx_dash_in_air_right;

    Animation* current_dash_animation = nullptr;

    std::vector<Barb*> barb_list;
    std::vector<Sword*> sword_list;

    CollisionBox* collision_box_silk = nullptr;

};

#endif //HOLLOWKNIGHT_DEMO_SCRIPTS_ENEMY_H_
