#include "Knight.h"



Knight::Knight() {
    animation_idle_left.set_atlas(&atlas_knight_idle_left);
    animation_idle_right.set_atlas(&atlas_knight_idle_right);
    animation_knight_start_run_left.set_atlas(&atlas_knight_start_run_left);
    animation_knight_start_run_right.set_atlas(&atlas_knight_start_run_right);
    animation_run_left.set_atlas(&atlas_knight_run_left);
    animation_run_right.set_atlas(&atlas_knight_run_right);

    animation_idle_left.set_interval(FRAME);
    animation_idle_right.set_interval(FRAME);
    animation_knight_start_run_left.set_interval(FRAME*4);
    animation_knight_start_run_right.set_interval(FRAME*4);
    animation_run_left.set_interval(FRAME*8);
    animation_run_right.set_interval(FRAME*8);
}
void Knight::on_input(const ExMessage& msg){
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
                    on_jump();
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
            }
            break;
        default:
            break;
    }
}

void Knight::on_update(int delta) {
    int direction = is_right_key_down - is_left_key_down;
    if(direction != 0){
        is_facing_right = direction > 0;
        if(start_run < FRAME / 3){
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
    }
    else{
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        start_run = 0;
    }

    current_animation->on_update(delta);

    move_and_collide(delta);
}

void Knight::on_draw(const Camera &camera) {
    current_animation->on_draw((int)position.x, (int)position.y);
}

void Knight::move_and_collide(int delta){
    velocity.y += gravity * delta;
    position += velocity * (float)delta;
    if(velocity.y > 0){
        if(position.y > 520){
            velocity.y = 0;
            position.y = 520;
        }
    }
}
