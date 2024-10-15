#include <algorithm>
#include "enemy.h"
#include "state_machine.h"
#include "enemy_state_node.h"

Enemy::Enemy() {
    is_facing_left = false;
    position = {1050, 100};
    logic_height = 150;
    hp += 5;

    hit_box->set_layer_src(CollisionLayer::None);
    hit_box->set_layer_dst(CollisionLayer::Player);

    hurt_box->set_layer_src(CollisionLayer::Enemy);
    hurt_box->set_layer_dst(CollisionLayer::None);

    hit_box->set_size({40, 100});
    hurt_box->set_size({80, 120});

    hurt_box->set_on_collide([&]() {
        de_hp();
    });

    collision_box_silk = CollisionManager::instance()->create_collision_box();
    collision_box_silk->set_size({270, 270});
    collision_box_silk->set_layer_src(CollisionLayer::None);
    collision_box_silk->set_layer_dst(CollisionLayer::Player);
    collision_box_silk->set_enabled(false);

    collision_box_dash = CollisionManager::instance()->create_collision_box();
    collision_box_dash->set_size({100, 50});
    collision_box_dash->set_layer_src(CollisionLayer::None);
    collision_box_dash->set_layer_dst(CollisionLayer::Player);
    collision_box_dash->set_enabled(false);

    {
        animation_silk.set_atlas(&atlas_silk);
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
        animation_vfx_dash_on_floor_left.set_atlas(&atlas_vfx_dash_on_floor_left);
        animation_vfx_dash_on_floor_right.set_atlas(&atlas_vfx_dash_on_floor_right);

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
        state_machine.register_state("aim", new EnemyAimState());
        state_machine.register_state("dash_in_air", new EnemyDashInAirState());
        state_machine.register_state("dash_on_floor", new EnemyDashOnFloorState());
        state_machine.register_state("dead", new EnemyDeadState());
        state_machine.register_state("fall", new EnemyFallState);
        state_machine.register_state("idle", new EnemyIdleState());
        state_machine.register_state("jump", new EnemyJumpState());
        state_machine.register_state("run", new EnemyRunState());
        state_machine.register_state("squat", new EnemySquatState());
        state_machine.register_state("throw_barb", new EnemyThrowBarbState());
        state_machine.register_state("throw_silk", new EnemyThrowSilkState());
        state_machine.register_state("throw_sword", new EnemyThrowSwordState());

        state_machine.set_entry("idle");
    }

    {
        timer_invulnerable_status.set_wait_time(60);
        timer_invulnerable_status.set_one_shot(true);
        timer_invulnerable_status.set_callback([&]() {
            is_invulnerable = false;
        });
        timer_invulnerable_blink.set_wait_time(5);
        timer_invulnerable_blink.set_one_shot(false);
        timer_invulnerable_blink.set_callback([&]() {
            is_blink_invisible = !is_blink_invisible;
        });
    }
}

Enemy::~Enemy() {
    CollisionManager::instance()->destroy_collision_box(collision_box_silk);
}

void Enemy::on_update(int delta) {
    if (velocity.x >= 0.0001f) {
        is_facing_left = (velocity.x < 0);
    }
    // 本应在Player::on_update中处理的逻辑
    if (hp <= 0)
        velocity.x = 0;
    if (enable_gravity)
        velocity.y += GRAVITY * delta / 1000.0f / FRAME / 1000.f;

    position += velocity * delta;

    if (position.y >= FLOOR_Y) {
        position.y = FLOOR_Y;
        velocity.y = 0;
    }

    hurt_box->set_position(position + Vector2(20, 20));

//    if (!current_animation)
//        return;

    if (!is_on_debug) {
        if (current_animation)
            current_animation->on_update(delta);
    }
    if (!is_on_debug)
        state_machine.on_update(delta);
    timer_invulnerable_status.on_update(delta);
    if (is_invulnerable) {
        timer_invulnerable_blink.on_update(delta);
    }
    Player::on_update(delta);

    hit_box->set_position(position + Vector2(40, 30));

    if (is_throwing_silk) {
        collision_box_silk->set_position(position + Vector2(-75, -60));
        collision_box_silk->set_enabled(true);
        animation_silk.on_update(delta);
    }
    if (is_on_debug) {
        if (is_dashing_in_air || is_dashing_on_floor) {
            current_animation = is_facing_left ? &animation_dash_in_air_left : &animation_dash_in_air_right;
        } else
            current_animation = is_facing_left ? &animation_idle_left : &animation_idle_right;
        if (current_animation)
            current_animation->on_update(delta);
    } else if (is_dashing_in_air || is_dashing_on_floor) {
        if (current_dash_animation) {
            current_dash_animation->on_update(delta);
        }
    }

    for (Barb* barb : barb_list)
        barb->on_update(delta);
    for (Sword* sword : sword_list)
        sword->on_update(delta);
    barb_list.erase(std::remove_if(barb_list.begin(), barb_list.end(), [](Barb* barb) {
        bool can_remove = !barb->is_valid_barb();
        if (can_remove) delete barb;
        return can_remove;
    }), barb_list.end());

    sword_list.erase(std::remove_if(sword_list.begin(), sword_list.end(), [](Sword* sword) {
        bool can_remove = !sword->is_valid_sword();
        if (can_remove) delete sword;
        return can_remove;
    }), sword_list.end());

    if (animation_silk.check_finished()) {
        is_throwing_silk = false;
        collision_box_silk->set_enabled(false);
        animation_silk.reset();
    }
}

void Enemy::on_draw(const Camera& camera) {
    for (Barb* barb : barb_list)
        barb->on_draw(camera);

    for (Sword* sword : sword_list)
        sword->on_draw(camera);

    Player::on_draw(camera);

    if (is_throwing_silk) {
        animation_silk.on_draw(position.x - 75.0f, position.y - 70.0f);
    }

    if (is_dashing_in_air || is_dashing_on_floor) {
        if (is_on_debug) {

        } else {
            if (current_dash_animation) {
                if (current_animation == &animation_dash_on_floor_left) {
                    current_dash_animation->on_draw(position.x - 450, position.y);
                    collision_box_dash->set_position(position - Vector2(80, -100));
                    collision_box_dash->set_enabled(true);
                } else if (current_animation == &animation_dash_on_floor_right) {
                    collision_box_dash->set_position(position + Vector2(130, 100));
                    collision_box_dash->set_enabled(true);
                    current_dash_animation->on_draw(position.x - 20, position.y);
                } else if (current_animation == &animation_dash_in_air_left) {
                    current_dash_animation->on_draw(position.x - 500, position.y);
                } else {
                    current_dash_animation->on_draw(position.x, position.y);
                }
            }
        }
    }
}

void Enemy::throw_barbs() {
    int num_new_barb = generate_random_number(3, 6);
    //std::cout << num_new_barb << std::endl;

    if (barb_list.size() >= 8) num_new_barb = 1;
    int width_grid = getwidth() / num_new_barb;

    for (int i = 0; i < num_new_barb; i++) {
        Barb* barb = new Barb();
        int rand_x = generate_random_number(width_grid * i, width_grid * (i + 1));
        int rand_y = generate_random_number(250, 500);
        barb->set_position({(float) rand_x, (float) rand_y});
        barb_list.push_back(barb);
    }
}

void Enemy::throw_sword() {
    Sword* sword = new Sword(position, is_facing_left);
    sword_list.push_back(sword);
    //std::cout << sword->is_valid_sword() << std::endl;

}

void Enemy::on_dash() {
    if (is_dashing_in_air)
        current_dash_animation = velocity.x < 0 ? &animation_vfx_dash_in_air_left : &animation_vfx_dash_in_air_right;
    else if (is_dashing_on_floor)
        current_dash_animation = velocity.x < 0 ? &animation_vfx_dash_on_floor_left : &animation_vfx_dash_on_floor_right;
    current_dash_animation->reset();
}

void Enemy::on_throw_silk() {
    is_throwing_silk = true;
    animation_silk.reset();
}

void Enemy::on_input(const ExMessage& msg) {
    switch (msg.message) {
        case WM_KEYDOWN:
            switch (msg.vkcode) {
                case 0x57: // W
                    // Handle W key press
                    break;
                case 0x41: // A
                    velocity.x = -(12.0f / FRAME);
                    is_dashing_in_air = true;
                    is_facing_left = true;
                    break;
                case 0x53: // S
                    // Handle S key press
                    break;
                case 0x44: // D
                    velocity.x = 12.0f / FRAME;
                    //std::cout << "position.x = " << position.x << std::endl;
                    is_dashing_in_air = true;
                    is_facing_left = false;
                    break;
                case 0x46: // F
                    throw_sword();
                    break;
                case 0x47: // G
                    throw_barbs();
                    break;
                case 0x48: // H
                    on_throw_silk();
                    break;
            }
            break;
        case WM_KEYUP:
            switch (msg.vkcode) {
                case 0x57: // W
                    // Handle W key press
                    break;
                case 0x41: // A
                    velocity.x = 0;
                    is_dashing_in_air = false;
                    is_facing_left = true;
                    break;
                case 0x53: // S
                    // Handle S key press
                    break;
                case 0x44: // D
                    velocity.x = 0;
                    //std::cout << "position.x = " << position.x << std::endl;
                    is_dashing_in_air = false;
                    is_facing_left = false;
                    break;
            }
            break;
        default:break;
    }
}

void Enemy::switch_state(const std::string& id) {
    state_machine.switch_to(id);
}

void Enemy::set_animation(const std::string& id) {
    if (id == "aim") {
        current_animation = is_facing_left ? &animation_aim_left : &animation_aim_right;
        animation_aim_left.reset();
        animation_aim_right.reset();
    } else if (id == "dash_in_air") {
        current_animation = is_facing_left ? &animation_dash_in_air_left : &animation_dash_in_air_right;
        animation_dash_in_air_left.reset();
        animation_dash_in_air_right.reset();
    } else if (id == "dash_on_floor") {
        current_animation = is_facing_left ? &animation_dash_on_floor_left : &animation_dash_on_floor_right;
        animation_dash_on_floor_left.reset();
        animation_dash_on_floor_right.reset();
    } else if (id == "fall") {
        current_animation = is_facing_left ? &animation_fall_left : &animation_fall_right;
        animation_fall_left.reset();
        animation_fall_right.reset();
    } else if (id == "idle") {
        current_animation = is_facing_left ? &animation_idle_left : &animation_idle_right;
        animation_idle_left.reset();
        animation_idle_right.reset();
    } else if (id == "jump") {
        current_animation = is_facing_left ? &animation_jump_left : &animation_jump_right;
        animation_jump_left.reset();
        animation_jump_right.reset();
    } else if (id == "run") {
        current_animation = is_facing_left ? &animation_run_left : &animation_run_right;
        animation_run_left.reset();
        animation_run_right.reset();
    } else if (id == "squat") {
        current_animation = is_facing_left ? &animation_squat_left : &animation_squat_right;
        animation_squat_left.reset();
        animation_squat_right.reset();
    } else if (id == "throw_barb") {
        current_animation = is_facing_left ? &animation_throw_barb_left : &animation_throw_barb_right;
        animation_throw_barb_left.reset();
        animation_throw_barb_right.reset();
    } else if (id == "throw_sword") {
        current_animation = is_facing_left ? &animation_throw_sword_left : &animation_throw_sword_right;
        animation_throw_sword_left.reset();
        animation_throw_sword_right.reset();
    } else if (id == "throw_silk") {
        current_animation = is_facing_left ? &animation_throw_silk_left : &animation_throw_silk_right;
        animation_throw_silk_left.reset();
        animation_throw_silk_right.reset();
    }
}

void Enemy::on_hurt() {

}
