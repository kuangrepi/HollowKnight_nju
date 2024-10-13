#include "Knight.h"

Knight::Knight() {
    animation_idle_left.set_atlas(&atlas_knight_idle_left);
    animation_idle_right.set_atlas(&atlas_knight_idle_right);
    animation_knight_start_run_left.set_atlas(&atlas_knight_start_run_left);
    animation_knight_start_run_right.set_atlas(&atlas_knight_start_run_right);
    animation_run_left.set_atlas(&atlas_knight_run_left);
    animation_run_right.set_atlas(&atlas_knight_run_right);
    animation_jump_start_left.set_atlas(&atlas_knight_jump_start_left);
    animation_jump_start_right.set_atlas(&atlas_knight_jump_start_right);
    animation_jump_loop_left.set_atlas(&atlas_knight_jump_loop_left);
    animation_jump_loop_right.set_atlas(&atlas_knight_jump_loop_right);
    animation_jump_land_left.set_atlas(&atlas_knight_jump_land_left);
    animation_jump_land_right.set_atlas(&atlas_knight_jump_land_right);


    logic_height = 120;

    hit_box->set_size({150, 150});
    hurt_box->set_size({40, 100});

    hit_box->set_layer_src(CollisionLayer::None);
    hit_box->set_layer_dst(CollisionLayer::Enemy);

    hurt_box->set_layer_src(CollisionLayer::Player);
    hurt_box->set_layer_dst(CollisionLayer::None);

    hit_box->set_enabled(false);

    hurt_box->set_on_collide([&]() {
        //TODO decrease_hp();
    });

    animation_idle_left.set_interval(FRAME*2);
    animation_idle_right.set_interval(FRAME*2);
    animation_knight_start_run_left.set_interval(FRAME*6);
    animation_knight_start_run_right.set_interval(FRAME*6);
    animation_run_left.set_interval(FRAME*6);
    animation_run_right.set_interval(FRAME*6);
    animation_jump_start_left.set_interval(FRAME*3);
    animation_jump_start_right.set_interval(FRAME*3);
    animation_jump_loop_left.set_interval(FRAME*6);
    animation_jump_loop_right.set_interval(FRAME*6);
    animation_jump_land_left.set_interval(FRAME*6);
    animation_jump_land_right.set_interval(FRAME*6);
}
void Knight::on_input(const ExMessage& msg) {
    switch (msg.message) {
        case WM_KEYDOWN:
            switch (msg.vkcode) {
                case VK_LEFT: // <-
                    is_left_key_down = true;
                    break;
                case VK_RIGHT: // ->
                    is_right_key_down = true;
                    break;
                case 0x5A: // Z
                    is_jump = true;
                    break;
            }
            break;
        case WM_KEYUP:
            switch (msg.vkcode) {
                case VK_LEFT: // <-
                    is_left_key_down = false;
                    break;
                case VK_RIGHT: // ->
                    is_right_key_down = false;
                    break;
                case 0x5A: // Z
                    is_jump = false;
                    break;
            }
            break;
        default:break;
    }
}

void Knight::on_update(int delta) {
    int direction = is_right_key_down - is_left_key_down;
    if (direction != 0) {
        is_facing_right = direction > 0;

            if(start_run < FRAME / 6){
                current_animation = is_facing_right ? &animation_knight_start_run_right : &animation_knight_start_run_left;
                start_run++;
                animation_run_right.reset();
                animation_run_left.reset();
            }
            else{
                current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
                animation_knight_start_run_left.reset();
                animation_knight_start_run_right.reset();
            }


        float distance = direction * run_velocity * delta;
        on_run(distance);
    } else {
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        start_run = 0;
    }
    if(position.y <= 518) {
        if (position.y > 400 && velocity.y < 0 && (animation_jump_start_right.get_idx_frame() < 11 || animation_jump_start_left.get_idx_frame() < 11)) {
            current_animation = is_facing_right ? &animation_jump_start_right : &animation_jump_start_left;
        } else {
            current_animation = is_facing_right ? &animation_jump_loop_right : &animation_jump_loop_left;
            if(velocity.y > 0) {
                animation_jump_start_left.reset();
                animation_jump_start_right.reset();
            }
        }
    }
    else if (is_land) {
        current_animation = is_facing_right ? &animation_jump_land_right : &animation_jump_land_left;
        if(animation_jump_land_right.get_idx_frame() == 2 || animation_jump_land_left.get_idx_frame() == 2){
            animation_jump_land_left.reset();
            animation_jump_land_right.reset();
            is_land = false;
        }

    }

    if (position.y >= 520){
        start_jump = 1;
    }
    if(is_jump) on_jump();

    current_animation->on_update(delta);
    position_hurt_box.x = position.x + 15;
    position_hurt_box.y = position.y + 20;
    hurt_box->set_position(position_hurt_box);
    Player::on_update(delta);

    move_and_collide(delta);

}

void Knight::on_draw(const Camera& camera) {
    current_animation->on_draw((int) position.x, (int) position.y);
    Player::on_draw(camera);
}

void Knight::move_and_collide(int delta){
    velocity.y += gravity * delta;
    position += velocity * (float)delta;
    if(velocity.y > 0){
        if(position.y > 520){
            if(velocity.y > 0.01) is_land = true;
            velocity.y = 0;
            position.y = 520;
        }
    }
}
