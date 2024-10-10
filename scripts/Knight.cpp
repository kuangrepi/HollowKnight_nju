#include "Knight.h"



Knight::Knight() {
    animation_idle_left.set_atlas(&atlas_knight_idle_left);
    animation_idle_right.set_atlas(&atlas_knight_idle_right);
}
void Knight::on_input(const ExMessage& msg){
    switch (msg.message) {
        case WM_KEYDOWN:
            switch (msg.vkcode) {
                case 0x41: // A
                    is_left_key_down = true;
                    break;
                case 0x44: // D
                    is_left_key_down = true;
                    break;
            }
            break;
        case WM_KEYUP:
            switch (msg.vkcode) {
                case VK_LEFT: // A
                    is_left_key_down = true;
                    break;
                case VK_RIGHT: // D
                    is_left_key_down = true;
                    break;
            }
            break;
            break;
        default:
            break;
    }
}

void Knight::on_update(int delta) {
    int direction = is_right_key_down - is_left_key_down;

    if(direction != 0){
        is_facing_right = direction > 0;
    }
    current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
    current_animation->on_update(delta);
}

void Knight::on_draw(const Camera &camera) {
    current_animation->on_draw((int)position.x, (int)position.y);
}
