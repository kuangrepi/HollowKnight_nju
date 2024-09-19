#include <functional>


class Timer {
private:
    int pass_time = 0;              // 已过时间
    int wait_time = 0;              // 等待时间
    bool paused = false;            // 是否暂停
    bool shotted = false;           // 是否触发
    bool one_shot = false;          // 单次触发
    std::function<void()> callback; // 触发回调

public:
    Timer() = default;
    ~Timer() = default;

    void restart();

    void set_wait_time(int val);

    void set_one_shoot(bool flag);

    void set_callback(std::function<void()> callback);

    void pause();

    void resume();

    void on_update(int delta);

};

