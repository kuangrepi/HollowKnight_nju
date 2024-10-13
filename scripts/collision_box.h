#ifndef HOLLOWKNIGHT_DEMO_SCRIPTS_COLLISION_BOX_H_
#define HOLLOWKNIGHT_DEMO_SCRIPTS_COLLISION_BOX_H_

#include "Vector2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

class CollisionBox
{
    friend class CollisionManager;

public:

    bool is_collide(const CollisionBox& other) {
        return position.x < other.position.x + other.size.x &&
            position.x + size.x > other.position.x &&
            position.y < other.position.y + other.size.y &&
            position.y + size.y > other.position.y;
    }

    const Vector2& get_position() const {
        return position;
    }

    const Vector2& get_size() const {
        return size;
    }

    void set_enabled(bool enabled) {
        this->enabled = enabled;
    }

    void set_on_collide(std::function<void()> on_collide) {
        this->on_collide = on_collide;
    }

    void set_position(const Vector2& position) {
        this->position = position;
    }

    void set_size(const Vector2& size) {
        this->size = size;
    }

    void set_layer_src(CollisionLayer layer) {
        this->layer_src = layer;
    }

    void set_layer_dst(CollisionLayer layer) {
        this->layer_dst = layer;
    }

    CollisionBox(const CollisionBox&) = delete;
    CollisionBox& operator=(const CollisionBox&) = delete;
    CollisionBox() = default;
private:
    Vector2 position;
    Vector2 size;
    bool enabled = true;
    std::function<void()> on_collide = nullptr;
    CollisionLayer layer_src = CollisionLayer::None;
    CollisionLayer layer_dst = CollisionLayer::None;
    ~CollisionBox() = default;
};

#endif //HOLLOWKNIGHT_DEMO_SCRIPTS_COLLISION_BOX_H_
