#ifndef HOLLOWKNIGHT_DEMO_KNIGHT_H
#define HOLLOWKNIGHT_DEMO_KNIGHT_H


#include "player.h"
#include "Vector2.h"
#include "Animation.h"
#include "define.h"

extern Atlas atlas_knight_idle_left;
extern Atlas atlas_knight_idle_right;
extern Atlas atlas_knight_start_run_left;
extern Atlas atlas_knight_start_run_right;
extern Atlas atlas_knight_run_left;
extern Atlas atlas_knight_run_right;

class Knight:public Player
{
public:
    Knight();
    ~Knight() = default;

    void on_update(int delta) override;

    void on_input(const ExMessage& msg) override;

    void on_draw(const Camera& camera) override;

    void set_position(float x, float y){
        position.x = x;
        position.y = y;
    }

    void on_run(float distance){
        position.x += distance;
    }

private:
    Vector2 position;
    Animation animation_idle_left;
    Animation animation_idle_right;
    Animation animation_knight_start_run_left;
    Animation animation_knight_start_run_right;
    Animation animation_run_left;
    Animation animation_run_right;

    Animation* current_animation = nullptr;

    bool is_left_key_down = false;
    bool is_right_key_down = false;

    bool is_facing_right = true;

    int start_run = 0;
    const float run_velocity = 0.15f;
};


#endif //HOLLOWKNIGHT_DEMO_KNIGHT_H

