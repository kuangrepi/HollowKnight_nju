#ifndef HOLLOWKNIGHT_DEMO_ANIMATION_H
#define HOLLOWKNIGHT_DEMO_ANIMATION_H
#include "Atlas.h"
#include "util.h"
#include <functional>

class Animation{
private:
    int timer = 0;          // 计时器
    int interval = 0;       // 帧间隔
    int idx_frame = 0;      // 帧索引
    bool is_loop = true;    // 是否循环
    Atlas* atlas = nullptr;
    std::function<void()> callback;

public:

    Animation() = default;
    ~Animation() = default;

    void reset();

    void set_atlas(Atlas* new_atlas);

    void set_loop(bool flag);

    void set_interval(int ms);

    int get_idx_frame();

    IMAGE* get_frame();

    void set_callback(std::function<void()> callback);

    bool check_finished();

    void on_update(int delta);

    void on_draw(int x, int y) const;

};

#endif //HOLLOWKNIGHT_DEMO_ANIMATION_H


