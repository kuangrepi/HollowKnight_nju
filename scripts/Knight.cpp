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
    animation_attack_left_1.set_atlas(&altas_knight_attack_left_1);
    animation_attack_right_1.set_atlas(&altas_knight_attack_right_1);
    animation_attack_left_effect_1.set_atlas(&altas_knight_attack_left_effect_1);
    animation_attack_right_effect_1.set_atlas(&altas_knight_attack_right_effect_1);
    animation_attack_left_up.set_atlas(&altas_knight_attack_left_up);
    animation_attack_right_up.set_atlas(&altas_knight_attack_right_up);
    animation_attack_left_effect_up.set_atlas(&altas_knight_attack_left_effect_up);
    animation_attack_right_effect_up.set_atlas(&altas_knight_attack_right_effect_up);
    animation_attack_left_down.set_atlas(&altas_knight_attack_left_down);
    animation_attack_right_down.set_atlas(&altas_knight_attack_right_down);
    animation_attack_left_effect_down.set_atlas(&altas_knight_attack_left_effect_down);
    animation_attack_right_effect_down.set_atlas(&altas_knight_attack_right_effect_down);
    animation_damage_left.set_atlas(&altas_knight_damage_left);
    animation_damage_right.set_atlas(&altas_knight_damage_right);
    animation_damage_effect.set_atlas(&altas_knight_damage_effect);
    animation_death.set_atlas(&altas_knight_death);

    logic_height = 120;

    hit_box->set_size({150, 150});
    hurt_box->set_size({40, 100});

    hit_box->set_layer_src(CollisionLayer::None);
    hit_box->set_layer_dst(CollisionLayer::Enemy);

    hurt_box->set_layer_src(CollisionLayer::Player);
    hurt_box->set_layer_dst(CollisionLayer::None);

    hit_box->set_enabled(false);

    hurt_box->set_on_collide([&]() {
        if(!is_damage && damage > FRAME/3){
            decrease_hp();
            is_damage = true;
            is_attack = false;
            damage = 0;
            effect_position.x = position.x - 290;
            effect_position.y = position.y;
        }
    });

    animation_idle_left.set_interval(FRAME*2);
    animation_idle_right.set_interval(FRAME*2);
    animation_knight_start_run_left.set_interval(FRAME*6);
    animation_knight_start_run_right.set_interval(FRAME*6);
    animation_run_left.set_interval(FRAME*6);
    animation_run_right.set_interval(FRAME*6);
    animation_jump_start_left.set_interval(FRAME*2);
    animation_jump_start_right.set_interval(FRAME*2);
    animation_jump_loop_left.set_interval(FRAME*4);
    animation_jump_loop_right.set_interval(FRAME*4);
    animation_jump_land_left.set_interval(FRAME*4);
    animation_jump_land_right.set_interval(FRAME*4);
    animation_attack_left_1.set_interval(FRAME*4);
    animation_attack_right_1.set_interval(FRAME*4);
    animation_attack_left_effect_1.set_interval(FRAME*8);
    animation_attack_right_effect_1.set_interval(FRAME*8);
    animation_attack_left_up.set_interval(FRAME*4);
    animation_attack_right_up.set_interval(FRAME*4);
    animation_attack_left_effect_up.set_interval(FRAME*6);
    animation_attack_right_effect_up.set_interval(FRAME*6);
    animation_attack_left_down.set_interval(FRAME*4);
    animation_attack_right_down.set_interval(FRAME*4);
    animation_attack_left_effect_down.set_interval(FRAME*6);
    animation_attack_right_effect_down.set_interval(FRAME*6);
    animation_damage_left.set_interval(FRAME*4);
    animation_damage_right.set_interval(FRAME*4);
    animation_damage_effect.set_interval(FRAME*4);
    animation_death.set_interval(FRAME*8);
}
void Knight::on_input(const ExMessage& msg) {
    if(hp > 0)
        switch (msg.message) {
            case WM_KEYDOWN:
                switch (msg.vkcode) {
                    case VK_LEFT: // <-
                        is_left_key_down = true;
                        break;
                    case VK_RIGHT: // ->
                        is_right_key_down = true;
                        break;
                    case VK_UP: // up
                        is_up_key_down = true;
                        break;
                    case VK_DOWN: // up
                        is_down_key_down = true;
                        break;
                    case 0x5A: // Z
                        is_jump = true;
                        break;
                    case 0x58: // X
                        if(!is_attack && !is_damage){
                            if(is_up_key_down && !is_down_key_down && !normal_attack && !down_attack){
                                effect_facing_right = is_facing_right;
                                effect_position.y = position.y-160;
                                animation_attack_left_effect_up.reset();
                                animation_attack_right_effect_up.reset();
                            }
                            else if(!is_up_key_down && !is_down_key_down && !up_attack && !down_attack){
                                effect_facing_right = is_facing_right;
                                effect_position.y = position.y;
                                animation_attack_left_effect_1.reset();
                                animation_attack_right_effect_1.reset();
                            }
                            else{
                                effect_facing_right = is_facing_right;
                                effect_position.y = position.y+100;
                                animation_attack_left_effect_down.reset();
                                animation_attack_right_effect_down.reset();
                            }
                        }
                        is_attack = true;
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
                    case VK_UP: // ->
                        is_up_key_down = false;
                        break;
                    case VK_DOWN: // ->
                        is_down_key_down = false;
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
    position_hurt_box.x = position.x + 15;
    position_hurt_box.y = position.y + 20;
    hurt_box->set_position(position_hurt_box);
    hit_box->set_position(position_hit_box);
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
        if (position.y > 350 && velocity.y < 0 && (animation_jump_start_right.get_idx_frame() < 11 || animation_jump_start_left.get_idx_frame() < 11)) {
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
    if(is_jump){
        on_jump();
        animation_knight_start_run_left.reset();
        animation_knight_start_run_right.reset();
    }

    if(is_attack && !is_damage && attack > FRAME / 6){
        if((is_up_key_down || up_attack) && !normal_attack && !down_attack){
            up_attack = true;
            normal_attack = false;
            down_attack = false;
            current_animation = is_facing_right ? &animation_attack_right_up : &animation_attack_left_up;
            if(animation_attack_right_up.get_idx_frame() == 4 || animation_attack_left_up.get_idx_frame() == 4){
                animation_attack_left_up.reset();
                animation_attack_right_up.reset();
                is_attack = false;
                up_attack = false;
                attack = 0;
            }
            hit_box->set_enabled(true);
            effect_position.y = position.y - 160;
            position_hit_box.x = effect_position.x+20;
            position_hit_box.y = effect_position.y+50;
            hit_box->set_size(Vector2(150,166));
            effect_animation = effect_facing_right ? &animation_attack_right_effect_up : &animation_attack_left_effect_up;
            if(animation_attack_right_effect_up.get_idx_frame() == 2 || animation_attack_left_effect_up.get_idx_frame() == 2){
                effect_animation = nullptr;
            }
        }
        else if((is_down_key_down || down_attack) && !normal_attack && !up_attack && position.y < 500){
            down_attack = true;
            normal_attack = false;
            up_attack = false;
            current_animation = is_facing_right ? &animation_attack_right_down : &animation_attack_left_down;
            if(animation_attack_right_down.get_idx_frame() == 4 || animation_attack_left_down.get_idx_frame() == 4){
                animation_attack_left_down.reset();
                animation_attack_right_down.reset();
                is_attack = false;
                down_attack = false;
                attack = 0;
            }
            hit_box->set_enabled(true);
            effect_position.y = position.y + 100;
            position_hit_box.x = effect_position.x+5;
            position_hit_box.y = effect_position.y+30;
            if(position_hit_box.y > 450){
                velocity.y += jump_velocity/7;
            }
            hit_box->set_size(Vector2(160,166));
            effect_animation = effect_facing_right ? &animation_attack_right_effect_down : &animation_attack_left_effect_down;
            if(animation_attack_right_effect_up.get_idx_frame() == 2 || animation_attack_left_effect_up.get_idx_frame() == 2){
                effect_animation = nullptr;
            }
        }
        else{
            normal_attack = true;
            up_attack = false;
            down_attack = false;
            current_animation = is_facing_right ? &animation_attack_right_1 : &animation_attack_left_1;
            if(animation_attack_right_1.get_idx_frame() == 4 || animation_attack_left_1.get_idx_frame() == 4){
                animation_attack_left_1.reset();
                animation_attack_right_1.reset();
                is_attack = false;
                normal_attack = false;
                attack = 0;
            }
            hit_box->set_enabled(true);
            effect_position.y = position.y;
            position_hit_box.x = effect_position.x+15;
            position_hit_box.y = effect_position.y+10;
            hit_box->set_size(Vector2(170,116));
            effect_animation = effect_facing_right ? &animation_attack_right_effect_1 : &animation_attack_left_effect_1;
            if(animation_attack_right_effect_1.get_idx_frame() == 2 || animation_attack_left_effect_1.get_idx_frame() == 2){
                effect_animation = nullptr;
            }
        }
    } else {
        if(animation_attack_right_effect_1.get_idx_frame() == 2 || animation_attack_left_effect_1.get_idx_frame() == 2){
            effect_animation = nullptr;
            animation_attack_right_effect_1.reset();
            animation_attack_left_effect_1.reset();
        }
        if(animation_attack_right_effect_up.get_idx_frame() == 2 || animation_attack_left_effect_up.get_idx_frame() == 2){
            effect_animation = nullptr;
            animation_attack_right_effect_up.reset();
            animation_attack_left_effect_up.reset();
        }
        if(animation_attack_right_effect_down.get_idx_frame() == 2 || animation_attack_left_effect_down.get_idx_frame() == 2){
            effect_animation = nullptr;
            animation_attack_right_effect_down.reset();
            animation_attack_left_effect_down.reset();
        }
        hit_box->set_enabled(false);
        animation_attack_left_1.reset();
        animation_attack_right_1.reset();
        animation_attack_left_up.reset();
        animation_attack_right_up.reset();
        animation_attack_left_down.reset();
        animation_attack_right_down.reset();
        attack++;
    }

    if(effect_facing_right && is_facing_right && !is_damage){
        if(is_up_key_down && !normal_attack){
            effect_position.x = position_hurt_box.x - 80;
        }
        else if(is_down_key_down && !normal_attack){
            effect_position.x = position_hurt_box.x - 75;
        }
        else if(!up_attack){
            effect_position.x = position_hurt_box.x - 10;
        }

    }
    if(!effect_facing_right && !is_facing_right && !is_damage){
        if(is_up_key_down && !normal_attack){
            effect_position.x = position_hurt_box.x - 80;
        }
        else if(is_down_key_down && !normal_attack){
            effect_position.x = position_hurt_box.x - 75;
        }
        else if(!up_attack){
            effect_position.x = position_hurt_box.x - 150;
        }

    }

    if(animation_damage_left.get_idx_frame() == 6 || animation_damage_right.get_idx_frame() == 6){
        is_damage = false;
        animation_damage_right.reset();
        animation_damage_left.reset();
        animation_damage_effect.reset();
    }
    if(is_damage){
        current_animation = is_facing_right ? &animation_damage_right : &animation_damage_left;
        effect_animation = &animation_damage_effect;
        if(effect_animation != nullptr && effect_animation->get_idx_frame() == 3){
            effect_animation = nullptr;
        }
    }
    if(damage < 1000){
        damage++;
    }
    move_and_collide(delta);
    if(hp <= 0){
        static int n = 0;
        if(n == 0){
            dead_position= position;
            n++;
        }
        position = dead_position;
        current_animation = &animation_death;
        if(current_animation->get_idx_frame() == 10)
            is_dead = true;
    }
    if(!is_dead)
        current_animation->on_update(delta);
    if(effect_animation != nullptr)
        effect_animation->on_update(delta);
    Player::on_update(delta);
}

void Knight::on_draw(const Camera& camera) {
    int width = current_animation->get_frame()->getwidth();

    if(is_facing_right && is_attack){
        current_animation->on_draw((int) position.x+66-width, (int) position.y);
    }
    else{
        current_animation->on_draw((int) position.x, (int) position.y);
    }
    if(effect_animation != nullptr)
        effect_animation->on_draw((int) effect_position.x, (int) effect_position.y);
    Player::on_draw(camera);

//    int width = current_animation->get_frame()->getwidth();
//    line(position.x + width, position.y, position.x + width, position.y+200);

//        std::cout << position_hurt_box.x << ' ';
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
