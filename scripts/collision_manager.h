#ifndef HOLLOWKNIGHT_DEMO_SCRIPTS_COLLISION_MANAGER_H_
#define HOLLOWKNIGHT_DEMO_SCRIPTS_COLLISION_MANAGER_H_

#include "collision_box.h"
#include <vector>

class CollisionManager
{
public:
    static CollisionManager* instance();

    CollisionBox* create_collision_box();
    void destroy_collision_box(CollisionBox* collision_box);

    void process_collision();
    void on_debug_draw();

private:
    static CollisionManager* manager;

    std::vector<CollisionBox*> collision_box_list;

    CollisionManager() = default;
    ~CollisionManager() = default;
};

#endif //HOLLOWKNIGHT_DEMO_SCRIPTS_COLLISION_MANAGER_H_
