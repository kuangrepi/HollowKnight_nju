#include "player.h"
#include "collision_manager.h"
#include "define.h"

Player::Player() {
    hit_box = CollisionManager::instance()->create_collision_box();
    hurt_box = CollisionManager::instance()->create_collision_box();

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

    for (int i = 0; i < 10; i++) {
        animation_blood_normal[i].set_atlas(&atlas_blood_normal);
        animation_blood_normal[i].set_interval(FRAME * 3);
        animation_blood_normal[i].set_loop(true);
    }
    for (int i = 0; i < 10; i++) {
        animation_blood_decrease[i].set_atlas(&atlas_blood_decrease);
        animation_blood_decrease[i].set_interval(FRAME * 3);
        animation_blood_decrease[i].set_loop(false);
    }

}

Player::~Player() {
    CollisionManager::instance()->destroy_collision_box(hit_box);
    CollisionManager::instance()->destroy_collision_box(hurt_box);
}

void Player::decrease_hp() {
    hp -= 1;
}

void Player::on_update(int delta) {
    if (position.x < 0) position.x = 0;
    if (position.x > getwidth() - 100) position.x = (float) getwidth() - 100;
    if (position.y < 0) position.y = 0;
    if (position.y > getheight() - 100) position.y = (float) getheight() - 100;

}

void Player::on_draw(const Camera& camera) {
    if (!current_animation || is_blink_invisible && is_invulnerable) return;
    current_animation->on_draw((int) position.x, (int) position.y);
}

void Player::on_input(const ExMessage& msg) {};

void Player::set_animation(Animation* animation) {
    current_animation = animation;
}