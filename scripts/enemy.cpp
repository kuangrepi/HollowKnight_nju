#include "enemy.h"

Enemy::Enemy() {
    is_facing_left = true;
    position = {1050, 200};
    logic_height = 150;

    hit_box->set_layer_src(CollisionLayer::None);
    hit_box->set_layer_dst(CollisionLayer::Player);

    hurt_box->set_layer_src(CollisionLayer::Enemy);
    hurt_box->set_layer_dst(CollisionLayer::None);

    hit_box->set_size({50, 80});
    hurt_box->set_size({100, 180});

    hurt_box->set_on_collide([&]() {
        decrease_hp();
    });

    collision_box_silk = CollisionManager::instance()->create_collision_box();
    collision_box_silk->set_size({225, 225});
    collision_box_silk->set_layer_src(CollisionLayer::None);
    collision_box_silk->set_layer_dst(CollisionLayer::Player);
    collision_box_silk->set_enabled(false);

    {
        animation_silk.set_atlas(&atlas_throw_silk_left);
        animation_aim_left.set_atlas(&atlas_aim_left);
        animation_aim_right.set_atlas(&atlas_aim_right);
        animation_dash_in_air_left.set_atlas(&atlas_dash_in_air_left);
        animation_dash_in_air_right.set_atlas(&atlas_dash_in_air_right);
        animation_dash_on_floor_left.set_atlas(&atlas_dash_on_floor_left);
        animation_dash_on_floor_right.set_atlas(&atlas_dash_on_floor_right);
        animation_fall_left.set_atlas(&atlas_fall_left);
        animation_fall_right.set_atlas(&atlas_fall_right);
        animation_idle_left.set_atlas(&atlas_idle_left);
        animation_idle_right.set_atlas(&atlas_idle_right);
        animation_jump_left.set_atlas(&atlas_jump_left);
        animation_jump_right.set_atlas(&atlas_jump_right);
        animation_run_left.set_atlas(&atlas_run_left);
        animation_run_right.set_atlas(&atlas_run_right);
        animation_squat_left.set_atlas(&atlas_squat_left);
        animation_squat_right.set_atlas(&atlas_squat_right);
        animation_throw_barb_left.set_atlas(&atlas_throw_barb_left);
        animation_throw_barb_right.set_atlas(&atlas_throw_barb_right);
        animation_throw_sword_left.set_atlas(&atlas_throw_sword_left);
        animation_throw_sword_right.set_atlas(&atlas_throw_sword_right);
        animation_throw_silk_left.set_atlas(&atlas_throw_silk_left);
        animation_throw_silk_right.set_atlas(&atlas_throw_silk_right);
        animation_vfx_dash_in_air_left.set_atlas(&atlas_vfx_dash_in_air_left);
        animation_vfx_dash_in_air_right.set_atlas(&atlas_vfx_dash_in_air_right);

        animation_silk.set_interval(FRAME * 3);
        animation_aim_left.set_interval(FRAME * 3);
        animation_aim_right.set_interval(FRAME * 3);
        animation_dash_in_air_left.set_interval(FRAME * 3);
        animation_dash_in_air_right.set_interval(FRAME * 3);
        animation_dash_on_floor_left.set_interval(FRAME * 3);
        animation_dash_on_floor_right.set_interval(FRAME * 3);
        animation_fall_left.set_interval(FRAME * 3);
        animation_fall_right.set_interval(FRAME * 3);
        animation_idle_left.set_interval(FRAME * 3);
        animation_idle_right.set_interval(FRAME * 3);
        animation_jump_left.set_interval(FRAME * 3);
        animation_jump_right.set_interval(FRAME * 3);
        animation_run_left.set_interval(FRAME * 3);
        animation_run_right.set_interval(FRAME * 3);
        animation_squat_left.set_interval(FRAME * 3);
        animation_squat_right.set_interval(FRAME * 3);
        animation_throw_barb_left.set_interval(FRAME * 3);
        animation_throw_barb_right.set_interval(FRAME * 3);
        animation_throw_sword_left.set_interval(FRAME * 3);
        animation_throw_sword_right.set_interval(FRAME * 3);
        animation_throw_silk_left.set_interval(FRAME * 3);
        animation_throw_silk_right.set_interval(FRAME * 3);
        animation_vfx_dash_in_air_left.set_interval(FRAME * 3);
        animation_vfx_dash_in_air_right.set_interval(FRAME * 3);

        animation_silk.set_loop(false);
        animation_aim_left.set_loop(false);
        animation_aim_right.set_loop(false);
        animation_dash_in_air_left.set_loop(true);
        animation_dash_in_air_right.set_loop(true);
        animation_dash_on_floor_left.set_loop(true);
        animation_dash_on_floor_right.set_loop(true);
        animation_fall_left.set_loop(true);
        animation_fall_right.set_loop(true);
        animation_idle_left.set_loop(false);
        animation_idle_right.set_loop(false);
        animation_jump_left.set_loop(false);
        animation_jump_right.set_loop(false);
        animation_run_left.set_loop(false);
        animation_run_right.set_loop(false);
        animation_squat_left.set_loop(false);
        animation_squat_right.set_loop(false);
        animation_throw_barb_left.set_loop(false);
        animation_throw_barb_right.set_loop(false);
        animation_throw_sword_left.set_loop(false);
        animation_throw_sword_right.set_loop(false);
        animation_throw_silk_left.set_loop(false);
        animation_throw_silk_right.set_loop(false);
        animation_vfx_dash_in_air_left.set_loop(false);
        animation_vfx_dash_in_air_right.set_loop(false);

    }
}