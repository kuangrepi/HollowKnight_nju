#ifndef HOLLOWKNIGHT_DEMO_KNIGHT_H
#define HOLLOWKNIGHT_DEMO_KNIGHT_H


#include "player.h"
#include "Vector2.h"
#include "Animation.h"
#include "define.h"

extern Atlas atlas_knight_idle_left;
extern Atlas atlas_knight_idle_right;

class Knight:public Player
{
public:
    Knight();
    ~Knight() = default;

    void on_update(int delta) override;

    void on_input(const ExMessage& msg) override;

    void on_draw(const Camera& camera) override;
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

