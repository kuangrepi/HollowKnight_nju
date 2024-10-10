#ifndef HOLLOWKNIGHT_DEMO_KNIGHT_H
#define HOLLOWKNIGHT_DEMO_KNIGHT_H


#include "player.h"
#include "Vector2.h"
#include "Animation.h"

class Knight:public Player
{
public:
    Knight() = default;
    ~Knight() = default;

    void on_update(int delta);

    void on_input(const ExMessage& msg);

    void on_draw(const Camera& camera);
private:
    Vector2 position;
    Animation animation_idle_left;
    Animation animation_idle_right;

    Animation* current_animation = nullptr;

    bool is_left_key_down = false;
    bool is_right_key_down = false;

    bool is_facing_right = true;
};


#endif //HOLLOWKNIGHT_DEMO_KNIGHT_H

