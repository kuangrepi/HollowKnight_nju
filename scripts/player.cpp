#include "player.h"
#include "collision_manager.h"

Player::Player() {
    hit_box = CollisionManager::instance()->create_collision_box();
    hurt_box = CollisionManager::instance()->create_collision_box();
}

Player::~Player() {
    CollisionManager::instance()->destroy_collision_box(hit_box);
    CollisionManager::instance()->destroy_collision_box(hurt_box);
}

void Player::on_update(int delta) {
    if (position.x < 0) position.x = 0;
    if (position.x > getwidth()) position.x = (float) getwidth();
    if (position.y < 0) position.y = 0;
    if (position.y > getheight()) position.y = (float) getheight();

    hurt_box->set_position(position);
}

void Player::on_draw(const Camera& camera) {
}