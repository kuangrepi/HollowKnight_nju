#include "Timer.h"

void Timer::on_update(int delta) {
    if (paused) return;

    pass_time += delta;

    if (pass_time >= wait_time){
        if((!one_shot || (one_shot && !shotted)) && callback){
            callback();
        }
        shotted = true;
        pass_time = 0;
    }
}