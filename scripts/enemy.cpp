#include "enemy.h"

Enemy::Enemy() {
    is_facing_left = true;
    position = {1050, 200};
    logic_height = 150;

    hit_box->set_layer_src(CollisionLayer::None);
    hit_box->set_layer_dst(CollisionLayer::Player);

    hurt_box->set_layer_src(CollisionLayer::Enemy);
    hurt_box->set_layer_dst(CollisionLayer::None);

    hit_box->set_size({50, 80});
    hurt_box->set_size({100, 180});

    hurt_box->set_on_collide([&]() {
        decrease_hp();
    });

    collision_box_silk = CollisionManager::instance()->create_collision_box();
    collision_box_silk->set_size({225, 225});
    collision_box_silk->set_layer_src(CollisionLayer::None);
    collision_box_silk->set_layer_dst(CollisionLayer::Player);
    collision_box_silk->set_enabled(false);

    {

    }
}