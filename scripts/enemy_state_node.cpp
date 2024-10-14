//
// Created by yzzhhy on 24-10-14.
//

#include "enemy.h"
#include "enemy_state_node.h"

EnemyAimState::EnemyAimState()
{
    timer.set_one_shot(true);
    timer.set_wait_time(0.5f);
    timer.set_on_timeout([&](){
        enemy->set_gravity_enabled(true);
        enemy->switch_state("dash_in_air");
    });
}

void EnemyAimState::on_enter()
{
    enemy->set_animation("aim");
    enemy->set_gravity_enabled(false);
    enemy->set_velocity(0.0, 0.0);
    timer.restart();
}

void EnemyAimState::on_update(float delta)
{
    timer.on_update(delta);
    if (enemy->get_hp() <= 0)
        enemy->switch_state("dead");
}

void EnemyDashInAirState::on_enter()
{
    enemy->set_animation("dash_in_air");

    const Player* player = knight_1;
    Vector2 pos_target = {player->get_position().x, floor};
    float length=sqrt((pos_target.x - enemy->get_position().x)*(pos_target.x - enemy->get_position().x) + (pos_target.y - enemy->get_position().y)*(pos_target.y - enemy->get_position().y));
//    enemy->set_velocity((pos_target - enemy->get_position())/length * SPEED_DASH);
    enemy->set_velocity((pos_target.x - enemy->get_position().x)/length* SPEED_DASH,(pos_target.y - enemy->get_position().y)/length*SPEED_DASH);
    enemy->set_dashing_in_air(true);
    enemy->set_gravity_enabled(false);
    enemy->on_dash();

//    play_audio_I("enemy_dash", false);
}

void EnemyDashInAirState::on_update(float delta)
{
    if(enemy->get_hp() <= 0)
        enemy->switch_state("dead");
    else if(enemy->is_on_floor())
        enemy->switch_state("idle");
}



void EnemyDashInAirState::on_exit()
{
    enemy->set_gravity_enabled(true);
    enemy->set_dashing_in_air(false);
}

EnemyDashOnFloorState::EnemyDashOnFloorState()
{
    timer.set_one_shot(true);
    timer.set_wait_time(0.5f);
    timer.set_on_timeout([this]()
    {
        enemy->set_dashing_on_floor(false);
    });
}

void EnemyDashOnFloorState::on_enter()
{
    enemy->set_animation("dash_on_floor");
    enemy->set_velocity(enemy->get_facing_left() ? -SPEED_DASH : SPEED_DASH, 0);
    enemy->set_dashing_on_floor(true);
    enemy->on_dash();
    timer.restart();
//    play_audio(_T("enemy_dash"), false);
}

void EnemyDashOnFloorState::on_update(float delta)
{
    timer.on_update(delta);
    if(enemy->get_hp() <= 0)
        enemy->switch_state("dead");
    else if (!enemy->get_dashing_on_floor())
        enemy->switch_state("idle");
}

void EnemyDeadState::on_enter()
{
    MessageBox(GetHWnd(), _T("很好，这样能行。"),_T("挑战成功！"),MB_OK);
    exit(0);
}

void EnemyFallState::on_enter()
{
    enemy->set_animation("fall");
}

void EnemyFallState::on_update(float delta)
{
    if (enemy->get_hp() <= 0)
        enemy->switch_state("dead");
    else if(enemy->is_on_floor())
        enemy->switch_state("idle");
}

EnemyIdleState::EnemyIdleState()
{
    timer.set_one_shot(true);
    timer.set_on_timeout([this]() {
        int rand_num = rand() % 100;;
        if (enemy->get_hp() > 5) {
            if (rand_num <= 25) {
                if (!enemy->is_on_floor())
                    enemy->switch_state("fall");
                else
                    enemy->switch_state("jump");  // 25%
            } else if (rand_num <= 50) {
                if (!enemy->is_on_floor())
                    enemy->switch_state("fall");
                else
                    enemy->switch_state("run");   // 25%
            } else if (rand_num <= 80)
                enemy->switch_state("squat");    // 30%
            else if (rand_num <= 90)
                enemy->switch_state("throw_silk");// 10%
            else
                enemy->switch_state("throw_sword");// 10%
        } else {
            if (rand_num <= 25) {
                if (!enemy->is_on_floor())
                    enemy->switch_state("fall");
                else
                    enemy->switch_state("jump");      // 25%
            } else if (rand_num <= 60)
                enemy->switch_state("throw_sword"); // 35%

            else if (rand_num <= 70)
                enemy->switch_state("throw_silk");   // 10%

            else if (rand_num <= 90)
                enemy->switch_state("throw_barb");   // 20%

            else
                enemy->switch_state("squat");         // 10%
        }
    });
}

void EnemyIdleState::on_enter()
{
    enemy->set_animation("idle");

    enemy->set_velocity( 0,0 );

    float wait_time = 0;
    if(enemy->get_hp() > 5)
        wait_time = (rand()%2+1)*0.25f;//0.05~0.5s
    else
        wait_time = rand()%4*0.125f;//0.05~0.25s

    timer.set_wait_time(wait_time);
    timer.restart();
}

void EnemyIdleState::on_update(float delta)
{
    timer.on_update(delta);

    if(enemy->get_hp() <= 0)
        enemy->switch_state("dead");
    else if(enemy->get_velocity().y>0)
        enemy->switch_state("fall");
}

void EnemyIdleState::on_exit()
{
    enemy->set_facing_left(enemy->get_position().x < knight_1->get_position().x);
}

void EnemyJumpState::on_enter()
{
    enemy->set_animation("jump");
    enemy->set_velocity(0, -SPEED_JUMP );
}

void EnemyJumpState::on_update(float delta)
{
    if (enemy->get_hp() <= 0)
        enemy->switch_state("dead");
    else if (enemy->get_velocity().y > 0)
    {
        int rand_num = rand()%100;
        if (enemy->get_hp() > 5)
        {
            if (rand_num <= 50)
                enemy->switch_state("aim");   // 50%
            else if (rand_num <= 80)
                enemy->switch_state("fall");  // 30%
            else
                enemy->switch_state("throw_silk"); // 20%
        }
        else
        {
            if (rand_num <= 50)
                enemy->switch_state("throw_silk"); // 50%
            else if (rand_num <= 80)
                enemy->switch_state("fall");  // 30%
            else
                enemy->switch_state("aim");   // 20%
        }
    }
}

void EnemyRunState::on_enter()
{
    enemy->set_animation("run");
//    play_audio(_T("enemy_run"), true);
}

void EnemyRunState::on_update(float delta)
{
    const Vector2& pos_enemy = enemy->get_position();
    const Vector2& pos_player =knight_1->get_position();
    enemy->set_velocity(pos_enemy.x < pos_player.x ? SPEED_RUN : -SPEED_RUN, 0);

    if(enemy->get_hp() <= 0)
        enemy->switch_state("dead");
    else if(abs(pos_enemy.x - pos_player.x) <= MIN_DIS)
    {
        int rand_num = rand()%100;
        if(enemy->get_hp() > 5)
        {
            if(rand_num <= 75)
                enemy->switch_state("squat");   // 75%
            else
                enemy->switch_state("throw_silk");   // 25%
        }
        else
        {
            if(rand_num <= 75)
                enemy->switch_state("throw_silk");   // 75%
            else
                enemy->switch_state("squat");         // 25%
        }
    }

//    stop_audio(_T("enemy_run"));
}

void EnemyRunState::on_exit()
{
    enemy->set_velocity(0, 0);
}

EnemySquatState::EnemySquatState()
{
    timer.set_one_shot(true);
    timer.set_wait_time(0.5f);
    timer.set_on_timeout([this]()
    {
        enemy->switch_state("dash_on_floor");});
}

void EnemySquatState::on_enter()
{
    enemy->set_animation("squat");
    enemy->set_facing_left(enemy->get_position().x > knight_1->get_position().x);
    timer.restart();
}

void EnemySquatState::on_update(float delta)
{
    timer.on_update(delta);
    if (enemy->get_hp() <= 0)
        enemy->switch_state("dead");
}

EnemyThrowBarbState::EnemyThrowBarbState()
{
    timer.set_one_shot(true);
    timer.set_wait_time(0.8f);
    timer.set_on_timeout([this]()
    {
        enemy->throw_barbs();
        enemy->switch_state("idle");
    });
}

void EnemyThrowBarbState::on_enter()
{
    enemy->set_animation("throw_barb");
    timer.restart();
//    play_audio(_T("enemy_throw_barbs"), false);
}

void EnemyThrowBarbState::on_update(float delta)
{
    timer.on_update(delta);

    if (enemy->get_hp() <= 0)
    {
        enemy->switch_state("dead");
    }
}

EnemyThrowSilkState::EnemyThrowSilkState()
{
    timer.set_one_shot(true);
    timer.set_wait_time(0.9f);
    timer.set_on_timeout([]()
    {
        enemy->set_gravity_enabled(true);
        enemy->set_throwing_silk(false);

        if (!enemy->is_on_floor() && enemy->get_hp() > 5 && rand()%100 <= 25)
            enemy->switch_state("aim");
        else if (enemy->is_on_floor())
            enemy->switch_state("fall");
        else
            enemy->switch_state("idle");
    });
}

void EnemyThrowSilkState::on_enter()
{
    enemy->set_animation("throw_silk");

    enemy->set_gravity_enabled(false);
    enemy->set_throwing_silk(true);
    enemy->set_velocity(0, 0);
    enemy->on_throw_silk();
    timer.restart();

//    play_audio(T("enemy_throw_silk"), false);
}

void EnemyThrowSilkState::on_update(float delta)
{
    timer.on_update(delta);
    if (enemy->get_hp() <= 0)
    {
        enemy->switch_state("dead");
    }
}

EnemyThrowSwordState::EnemyThrowSwordState()
{
    timer_throw.set_wait_time(0.65f);
    timer_throw.set_one_shot(true);
    timer_throw.set_on_timeout([this]()
    {
        enemy->throw_sword();
//        play_audio(_T("enemy_throw_sword"), false);
    });

    timer_switch.set_wait_time(1.0f);
    timer_switch.set_one_shot(true);
    timer_switch.set_on_timeout([this]()
    {
        int rand_num = rand()%100;
        if(enemy->get_hp() > 5)
        {
            if(rand_num < 50)
                enemy->switch_state("squat");   // 50%
                else if(rand_num < 80)
                    enemy->switch_state("jump");    // 30%
                    else
                        enemy->switch_state("idle");    // 20%
        }
        else
        {
            if(rand_num < 50)
                enemy->switch_state("jump");    // 50%
                else if(rand_num < 80)
                    enemy->switch_state("throw_silk");// 30%
                    else
                        enemy->switch_state("idle");    // 20%
        }
    });
}

void EnemyThrowSwordState::on_enter()
{
    enemy->set_animation("throw_sword");
    timer_throw.restart();
    timer_switch.restart();
}

void EnemyThrowSwordState::on_update(float delta)
{
    timer_throw.on_update(delta);
    timer_switch.on_update(delta);

    if (enemy->get_hp() <= 0)
    {
        enemy->switch_state("dead");
    }
}

