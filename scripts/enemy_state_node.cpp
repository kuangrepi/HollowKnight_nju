//
// Created by yzzhhy on 24-10-14.
//

#include "enemy.h"
#include "enemy_state_node.h"
//
//EnemyAimState::EnemyAimState()
//{
//    timer.set_one_shot(true);
//    timer.set_wait_time(0.5f);
//    timer.set_on_timeout([&](){
//        enemy->set_gravity_enabled(true);
//        enemy->switch_state("dash_in_air");
//    });
//}
//
//void EnemyAimState::on_enter()
//{
//    enemy->set_animation("aim");
//    enemy->set_gravity_enabled(false);
//    enemy->set_velocity(0.0, 0.0);
//    timer.restart();
//}
//
//void EnemyAimState::on_update(float delta)
//{
//    timer.on_update(delta);
//    if (enemy->get_hp() <= 0)
//        enemy->switch_state("dead");
//}
//
//void EnemyDashInAirState::on_enter()
//{
//    enemy->set_animation("dash_in_air");
//
//    const Character* player = CharacterManager::instance()->get_player();
//    Vector2 pos_target = {player->get_position().x, player->get_floor_y()};
//    enemy->set_velocity((pos_target - enemy->get_position()).normalize() * SPEED_DASH);
//    enemy->set_dashing_in_air(true);
//    enemy->set_gravity_enabled(false);
//    enemy->on_dash();
//
////    play_audio_I("enemy_dash", false);
//}
//
//void EnemyDashInAirState::on_update(float delta)
//{
//    if(enemy->get_hp() <= 0)
//        enemy->switch_state("dead");
//    else if(enemy->is_on_floor())
//        enemy->switch_state("idle");
//}
//
//void EnemyDashInAirState::on_exit()
//{
//    enemy->set_gravity_enabled(true);
//    enemy->set_dashing_in_air(false);
//}
