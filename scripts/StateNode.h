//
// Created by yzzhhy on 24-10-13.
//

#ifndef HOLLOWKNIGHT_DEMO_STATENODE_H
#define HOLLOWKNIGHT_DEMO_STATENODE_H


class StateNode {
public:
    StateNode() = default;
    ~StateNode() = default;

    virtual void on_enter() {}
    virtual void on_update(float delta) {}
    virtual void on_exit() {}

};


#endif //HOLLOWKNIGHT_DEMO_STATENODE_H
