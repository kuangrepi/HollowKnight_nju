#include "Knight.h"



Knight::Knight() {
    animation_idle_left.set_atlas(&atlas_knight_idle_left);
    animation_idle_right.set_atlas(&atlas_knight_idle_right);
    animation_knight_start_run_left.set_atlas(&atlas_knight_start_run_left);
    animation_knight_start_run_right.set_atlas(&atlas_knight_start_run_right);
    animation_run_left.set_atlas(&atlas_knight_run_left);
    animation_run_right.set_atlas(&atlas_knight_run_right);

    animation_idle_left.set_interval(INTERVAL);
    animation_idle_right.set_interval(INTERVAL);
    animation_knight_start_run_left.set_interval(INTERVAL*6);
    animation_knight_start_run_right.set_interval(INTERVAL*6);
    animation_run_left.set_interval(INTERVAL*6);
    animation_run_right.set_interval(INTERVAL*6);
}
void Knight::on_input(const ExMessage& msg){
    switch (msg.message) {
        case WM_KEYDOWN:
            switch (msg.vkcode) {
                case 0x41: // A
                    is_left_key_down = true;
                    break;
                case 0x44: // D
                    is_right_key_down = true;
                    break;
            }
            break;
        case WM_KEYUP:
            switch (msg.vkcode) {
                case 0x41: // A
                    is_left_key_down = false;
                    break;
                case 0x44: // D
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
        if(start_run < 16){
            current_animation = is_facing_right ? &animation_knight_start_run_right : &animation_knight_start_run_left;
            start_run++;
        }
        else{
            current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
        }

        float distance = direction * run_velocity * delta;
        on_run(distance);
    }
    else{
        current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
        start_run = 0;
    }

    current_animation->on_update(delta);
}

void Knight::on_draw(const Camera &camera) {
    current_animation->on_draw((int)position.x, (int)position.y);
}
