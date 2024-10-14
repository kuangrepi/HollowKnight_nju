#include "sword.h"

Sword::Sword() {
    position = Vector2(0, 0);
    velocity = Vector2(0, 0);
    box = CollisionManager::instance()->create_collision_box();
}

Sword::Sword(Vector2 pos, bool is_left) {
    position = pos + Vector2(0, 60);
    velocity = Vector2(is_left ? -speed : speed, 0);
    box = CollisionManager::instance()->create_collision_box();
    box->set_position(position);
    box->set_size(Vector2(195, 10));
    box->set_layer_dst(CollisionLayer::Player);
    box->set_layer_src(CollisionLayer::None);

    animation.set_atlas(is_left ? &atlas_sword_left : &atlas_sword_right);
    animation.set_interval(FRAME);
    animation.set_loop(true);
}

Sword::~Sword() {
    CollisionManager::instance()->destroy_collision_box(box);
}

bool Sword::is_valid_sword() const {
    return is_valid;
}

void Sword::on_update(int delta) {
    position += velocity * delta;
    box->set_position(position);
    animation.on_update(delta);

    if (position.x < -200 || position.x > 1280 + 200) {
        is_valid = false;
    }
}

void Sword::on_draw(const Camera& camera) {
    animation.on_draw((int) position.x, (int) position.y);
}
