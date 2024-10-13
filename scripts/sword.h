#ifndef HOLLOWKNIGHT_DEMO_SCRIPTS_SWORD_H_
#define HOLLOWKNIGHT_DEMO_SCRIPTS_SWORD_H_

#include "Vector2.h"
#include "collision_manager.h"
#include "Animation.h"
#include "define.h"
#include "Camera.h"

extern Atlas atlas_sword;

class Sword
{
public:
    Sword();
    Sword(Vector2 pos, bool is_left);
    ~Sword();
    bool is_valid_sword() const;
    void on_update(int delta);
    void on_draw(const Camera& camera);
private:
    const float speed = 12.0f / FRAME;
    Vector2 position;
    Vector2 velocity;
    bool is_valid;
    CollisionBox* box;
    Animation animation;
};

#endif //HOLLOWKNIGHT_DEMO_SCRIPTS_SWORD_H_
