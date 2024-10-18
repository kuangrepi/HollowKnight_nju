#include "barb.h"

Barb::Barb() {
    diff_period = generate_random_number(0, 6);

    animation_loose.set_atlas(&atlas_barb_loose);
    animation_break.set_atlas(&atlas_barb_break);
    animation_loose.set_loop(true);
    animation_break.set_loop(false);
    animation_loose.set_interval(FRAME);
    animation_break.set_interval(FRAME);
    animation_break.set_callback([&]() {
        is_valid = false;
    });

    collision_box = CollisionManager::instance()->create_collision_box();
    collision_box->set_position(cur_position + Vector2(15, 15));
    collision_box->set_size(Vector2(20, 20));
    collision_box->set_layer_src(CollisionLayer::Enemy);
    collision_box->set_layer_dst(CollisionLayer::Player);
    collision_box->set_on_collide([&]() {
        on_break();
    });

    timer_idle.set_wait_time((float) generate_random_number(180, 300));
    timer_idle.set_one_shot(true);
    timer_idle.set_callback([&]() {
        if (stage == Stage::Idle) {
            stage = Stage::Aim;
            base_position = cur_position;
        }
    });

    timer_aim.set_wait_time((float) 45);
    timer_aim.set_one_shot(true);
    timer_aim.set_callback([&]() {
        if (stage == Stage::Aim) {
            stage = Stage::Dash;
            const Vector2& knight_pos = knight_1->get_position();
            velocity = (knight_pos - cur_position).normalize() * speed;
        }
    });
}

Barb::~Barb() {
    if (collision_box) {
        CollisionManager::instance()->destroy_collision_box(collision_box);
    }
}

void Barb::set_position(Vector2 pos) {
    base_position = pos;
    cur_position = pos;
}

void Barb::on_update(int delta) {
    if (stage == Stage::Idle) {
        timer_idle.on_update(delta);
    }
    if (stage == Stage::Aim) {
        timer_aim.on_update(delta);
    }

    total_delta_time += 1;
    switch (stage) {
        case Stage::Idle:cur_position.y = base_position.y + sin(total_delta_time * 0.1f + diff_period * 20) * 10;
            break;
        case Stage::Aim:cur_position.x = base_position.x + generate_random_number(-10, 10);
            break;
        case Stage::Dash:cur_position += velocity * delta;
            if (cur_position.y + 120 > getheight()) {
                on_break();
            }
            if (cur_position.y <= 0) {
                is_valid = false;
            }
            break;
    }
    collision_box->set_position(cur_position + Vector2(15, 15));

    current_animation = (stage == Stage::Break) ? &animation_break : &animation_loose;
    current_animation->on_update(delta / 10);
    if (stage == Stage::Break && current_animation->check_finished()) {
        is_valid = false;
    }
}

void Barb::on_draw(const Camera& camera) {
    if (!current_animation) return;
    current_animation->on_draw((int) cur_position.x, (int) cur_position.y);
}

void Barb::on_break() {
    if (stage == Stage::Break) return;
    mciSendString(_T("play barb_break from 0"), NULL, 0, NULL);
    stage = Stage::Break;
    collision_box->set_enabled(false);
}

bool Barb::is_valid_barb() const {
    return is_valid;
}