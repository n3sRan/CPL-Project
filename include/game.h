//
// Created by n3sRa on 2024/1/23.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#define RADIUS_FLOAT 10
#define RADIUS_DECREASE 15
#define MAX_LEVEL 10
#define LEVEL_DIVIDE 4
#define MAX_SPEED 40
#define SPEED_DIVIDE 50
#define MAX_RADIUS 190
#define MIN_RADIUS 40

#define NORMAL_PLATFORM 0
#define SCORE_PLATFORM 1
#define PROPS_PLATFORM 2

#define WAITING_TIME 3000

#include "common.h"
#include "utils/input.h"
#include "utils/display.h"
#include "utils/audio.h"

typedef struct {
    unsigned int begin_time;
    bool write_enable;
} TimeCounter;

extern TimeCounter time_counter;

void do_menu_logic();

void do_game_logic();

void do_dead_logic();

void do_game_init();

void body_jump(unsigned int pressed_time);

void create_next_platform();

void alive_judge();

void next_step();

void bonus_check();

void highest_check();

void copy_platform();

int random_number(int range);

#endif //PROJECT_GAME_H
