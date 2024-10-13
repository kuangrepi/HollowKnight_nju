#ifndef HOLLOWKNIGHT_DEMO_SCRIPTS_BARB_H_
#define HOLLOWKNIGHT_DEMO_SCRIPTS_BARB_H_

#include "Camera.h"
#include "collision_box.h"
#include "Animation.h"
#include "define.h"
#include "Timer.h"

extern Atlas atlas_barb_loose;
extern Atlas atlas_barb_break;

class Barb
{
public:
    Barb();
    ~Barb();
    void set_position(Vector2 pos);
    bool is_valid_barb() const;
    void on_update(int delta);
    void on_draw(const Camera& camera);

private:
    enum class Stage
    {
        Idle,
        Aim,
        Dash,
        Break
    };
    const float speed = 6.0f / FRAME;

    Timer timer_idle;
    Timer timer_aim;
    int diff_period = 0;
    bool is_valid = true;
    float total_delta_time = 0;

    Vector2 base_position;
    Vector2 cur_position;
    Vector2 velocity;

    CollisionBox* box = nullptr;
    Animation animation_loose;
    Animation animation_break;
    Animation* current_animation = nullptr;

    void on_break();
};

#endif //HOLLOWKNIGHT_DEMO_SCRIPTS_BARB_H_
