//
// Created by yzzhhy on 24-10-13.
//

#ifndef HOLLOWKNIGHT_DEMO_ENEMY_STATE_NODE_H
#define HOLLOWKNIGHT_DEMO_ENEMY_STATE_NODE_H

#include "timer.h"
#include "state_node.h"

class EnemyAimState : public StateNode
{
public:
    EnemyAimState();
    ~EnemyAimState() = default;

    void on_enter() override;
    void on_update(float delta) override;

private:
    Timer timer;
};

class EnemyDashInAirState : public StateNode
{
public:
    EnemyDashInAirState() = default;
    ~EnemyDashInAirState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;
};


#endif //HOLLOWKNIGHT_DEMO_ENEMY_STATE_NODE_H
