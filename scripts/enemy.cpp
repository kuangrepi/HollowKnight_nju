#include <algorithm>
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
        animation_idle_left.set_loop(true);
        animation_idle_right.set_loop(true);
        animation_jump_left.set_loop(false);
        animation_jump_right.set_loop(false);
        animation_run_left.set_loop(true);
        animation_run_right.set_loop(true);
        animation_squat_left.set_loop(false);
        animation_squat_right.set_loop(false);
        animation_throw_barb_left.set_loop(false);
        animation_throw_barb_right.set_loop(false);
        animation_throw_sword_left.set_loop(false);
        animation_throw_sword_right.set_loop(false);
        animation_throw_silk_left.set_loop(true);
        animation_throw_silk_right.set_loop(true);
        animation_vfx_dash_in_air_left.set_loop(false);
        animation_vfx_dash_in_air_right.set_loop(false);
    }

    {
        // TODO: 状态机初始化
    }
}

Enemy::~Enemy() {
    CollisionManager::instance()->destroy_collision_box(collision_box_silk);
}

void Enemy::on_update(int delta) {
    if (velocity.x >= 0) {
        is_facing_left = false;
    }

    // 本应在Player::on_update中处理的逻辑
    if (hp <= 0)
        velocity.x = 0;
    if (enable_gravity)
        velocity.y += GRAVITY * delta;

    position += velocity * delta;

    if (position.y >= FLOOR_Y) {
        position.y = FLOOR_Y;
        velocity.y = 0;
    }

    hurt_box->set_position(position);

//    if (!current_animation)
//        return;

    current_animation->on_update(delta);

    Player::on_update(delta);

    hit_box->set_position(position);

    if (is_throwing_silk) {
        collision_box_silk->set_position(position);
        // ?    collision_box_silk->set_enabled(true);
        collision_box_silk->set_position(position);
        animation_silk.on_update(delta);
    }

    if (is_dashing_in_air || is_dashing_on_floor) {
        current_dash_animation->on_update(delta);
    }

//    for (Barb* barb : barb_list)
//        barb->on_update(delta);
    for (Sword* sword : sword_list)
        sword->on_update(delta);

//    barb_list.erase(std::remove_if(barb_list.begin(), barb_list.end(), [](Barb* barb) {
//        bool can_remove = !barb->is_valid_barb();
//        if (can_remove) delete barb;
//        return can_remove;
//    }), barb_list.end());

    sword_list.erase(std::remove_if(sword_list.begin(), sword_list.end(), [](Sword* sword) {
        bool can_remove = !sword->is_valid_sword();
        if (can_remove) delete sword;
        return can_remove;
    }), sword_list.end());
}

void Enemy::on_draw(const Camera& camera) {
    //    for (Barb* barb : barb_list)
//        barb->on_draw(camera);

    for (Sword* sword : sword_list)
        sword->on_draw(camera);

    Player::on_draw(camera);

    if (is_throwing_silk) {
        animation_silk.on_draw(position.x, position.y);
    }

    if (is_dashing_in_air || is_dashing_on_floor) {
        current_dash_animation->on_draw(position.x, position.y);
    }
}

void Enemy::throw_barbs() {
//    int num_new_barb = generate_random_number(3, 6);
//
//    if (barb_list.size() >= 10) num_new_barb = 1;
//    int width_grid = getwidth() / num_new_barb;
//
//    for (int i = 0; i < num_new_barb; i++) {
//        Barb* barb = new Barb();
//        int rand_x = generate_random_number(width_grid * i, width_grid * (i + 1));
//        int rand_y = generate_random_number(250, 500);
//        barb->set_position({(float) rand_x, (float) rand_y});
//        barb_list.push_back(barb);
//    }
}

void Enemy::throw_sword() {
    Sword* sword = new Sword(position, is_facing_left);
    sword_list.push_back(sword);
}

void Enemy::on_dash() {
    if (is_dashing_in_air)
        current_dash_animation = velocity.x < 0 ? &animation_dash_in_air_left : &animation_dash_in_air_right;
    else
        current_dash_animation = velocity.x < 0 ? &animation_dash_on_floor_left : &animation_dash_on_floor_right;
    current_dash_animation->reset();
}

void Enemy::on_throw_silk() {
    //is_throwing_silk = true;
    animation_silk.reset();
}

void Enemy::switch_state(const std::string& id){
    state_machine.switch_to(id);
}

void Enemy::set_animation(const std::string& id){
    current_animation = &animation_pool[id];
    is_facing_left = true;
}