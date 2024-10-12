#include "collision_manager.h"

#include <graphics.h>
#include <algorithm>

CollisionManager* CollisionManager::manager = nullptr;

CollisionManager* CollisionManager::instance() {
    if (manager == nullptr) {
        manager = new CollisionManager();
    }
    return manager;
}

CollisionBox* CollisionManager::create_collision_box() {
    CollisionBox* collision_box = new CollisionBox();
    collision_box_list.push_back(collision_box);
    return collision_box;
}

void CollisionManager::destroy_collision_box(CollisionBox* collision_box) {
    collision_box_list.erase(std::remove(collision_box_list.begin(), collision_box_list.end(), collision_box), collision_box_list.end());
    delete collision_box;
}

void CollisionManager::process_collision() {
    for (CollisionBox* collision_box_src : collision_box_list) {
        if (!collision_box_src->enabled && collision_box_src->layer_dst == CollisionLayer::None) {
            continue;
        }
        for (CollisionBox* collision_box_dst : collision_box_list) {
            if (!collision_box_dst->enabled || collision_box_dst->layer_dst == CollisionLayer::None
                || collision_box_src == collision_box_dst) {
                continue;
            }
            bool is_collide_x =
                std::max(collision_box_src->get_position().x + collision_box_src->get_size().x,
                         collision_box_dst->get_position().x + collision_box_dst->get_size().x) -
                    std::min(collision_box_src->get_position().x, collision_box_dst->get_position().x) <
                    collision_box_src->get_size().x + collision_box_dst->get_size().x;

            bool is_collide_y =
                std::max(collision_box_src->get_position().y + collision_box_src->get_size().y,
                         collision_box_dst->get_position().y + collision_box_dst->get_size().y) -
                    std::min(collision_box_src->get_position().y, collision_box_dst->get_position().y) <
                    collision_box_src->get_size().y + collision_box_dst->get_size().y;

            if (is_collide_x && is_collide_y && collision_box_dst->on_collide) {
                collision_box_dst->on_collide();
            }
        }
    }
}

void CollisionManager::on_debug_draw() {
    for (CollisionBox* collision_box : collision_box_list) {
        setlinecolor(collision_box->enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));
        rectangle(collision_box->get_position().x, collision_box->get_position().y,
                  collision_box->get_position().x + collision_box->get_size().x,
                  collision_box->get_position().y + collision_box->get_size().y);
    }
}