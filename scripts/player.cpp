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
    if (position.x > getwidth() - 100) position.x = (float) getwidth() - 100;
    if (position.y < 0) position.y = 0;
    if (position.y > getheight() - 100) position.y = (float) getheight() - 100;


}

void Player::on_draw(const Camera& camera) {
}