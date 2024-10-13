//
// Created by yzzhhy on 24-10-13.
//

#include "enemy_state_node.h"
#include "enemy.h"
//#include "character_manager.h"

EnemyAimState::EnemyAimState()
{
    timer.set_one_shot(true);
    timer.set_wait_time(0.5f);
    timer.set_on_timeout([this]()
    {
        Enemy* enemy = Enemy::instance()->get_enemy();
        enemy->set_gravity_enabled(true);
        enemy->switch_state("dash_in_air");
    });
}

void EnemyAimState::on_enter()
{
    CharacterManager::instance()->get_enemy()->set_animation("aim");
    Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
    enemy->set_gravity_enabled(false);
    enemy->set_velocity({ 0,0 });
    timer.restart();
}

void EnemyAimState::on_update(float delta)
{
    Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
    timer.on_update(delta);

    if (enemy->get_hp() <= 0)
    {
        enemy->switch_state("dead");
    }
}
