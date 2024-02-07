#include "game.h"

TimeCounter time_counter = {.write_enable = true};

TimeCounter waiting_counter = {.write_enable = false}; //not waiting

Body body;
Platform platform_current;
Platform platform_next;

void do_menu_logic() {
    draw_menu();
    puts("Menu");

    SDL_Event menu_event;
    while (SDL_WaitEvent(&menu_event)) {
        do_event(menu_event);
        if (app.keyboard[SDL_SCANCODE_ESCAPE]) {
            app.gaming=0;
            return;
        }
        if (app.keyboard[SDL_SCANCODE_RETURN]) {
            app.gaming = 1;
            return;
        }
    }
}

void do_game_logic() {
    do_game_init();
    draw_game_init();
    puts("Playing");

    SDL_Event game_event;
    while (1) {
        while (SDL_PollEvent(&game_event)) {
            do_event(game_event);
            if (app.keyboard[SDL_SCANCODE_ESCAPE]) {
                app.gaming = 0;
                return;
            }
            if (time_counter.write_enable && app.keyboard[SDL_SCANCODE_SPACE]) { //未计时且按下跳跃键
                time_counter.begin_time = SDL_GetTicks();
                time_counter.write_enable = false;
                if (waiting_counter.write_enable) waiting_counter.write_enable = false;
                Mix_HaltChannel(-1);
                jump_audio_start();
                continue;
            }
            if ((!time_counter.write_enable) && app.keyboard[SDL_SCANCODE_SPACE]) { //计时中
                if (Mix_Playing(-1) == 0) jump_audio_continue();
                continue;
            }
            if ((!time_counter.write_enable) && (!app.keyboard[SDL_SCANCODE_SPACE])) { //计时结束
                jump_audio_end();
                unsigned int pressed_time = SDL_GetTicks() - time_counter.begin_time;
                if (pressed_time <= 10) { //防中断
                    time_counter.write_enable = true;
                    continue;
                }
                body_jump(pressed_time);
                alive_judge();
                time_counter.write_enable = true;
                //printf("pressed_time = %d, body.x = %d, body.alive = %d score = %d\n", pressed_time, body.x, body.alive,body.score);
                if (body.alive == 0) {
                    app.gaming = 2;
                    return; //转到死亡界面
                }
            }
            if (body.perfect && app.keyboard[SDL_SCANCODE_RETURN]) {
                Mix_HaltChannel(-1);
                double need_time = (platform_next.x - body.x-BODY_W/2.0) / 25.0 * (SPEED_DIVIDE * 1.0);
                body_jump((int)need_time);
                body.perfect--;
                alive_judge();
            }
        }
        bonus_check();
        SDL_Delay(2);
    }
}

void do_dead_logic() {
    SDL_Delay(100);
    fail_audio();
    dead_body();
    draw_dead_menu();
    puts("Dead");
    SDL_Event dead_event;
    while (SDL_WaitEvent(&dead_event)) {
        do_event(dead_event);
        if (app.keyboard[SDL_SCANCODE_ESCAPE]) {
            app.gaming = 0;
            return;
        }
        if (app.keyboard[SDL_SCANCODE_RETURN]) {
            app.gaming = 1;
            return;
        }
    }
}

void do_game_init() {
    body.x = X_BEGIN - BODY_W / 2;
    body.y = MIDDLE_Y - BODY_H / 2 - 30;
    body.score = 0;
    body.special_score = 0;
    body.perfect = 0;
    body.alive = 1;

    platform_current.x = X_BEGIN;
    platform_current.radius = MAX_RADIUS;
    platform_current.type = NORMAL_PLATFORM;
    platform_current.isCircle = false;

    create_next_platform();
}

void create_next_platform() {
    //奖励平台出现概率为0.1, 道具平台出现概率为0.1
    int level = ((body.score - body.special_score) / LEVEL_DIVIDE) < MAX_LEVEL ? ((body.score - body.special_score) / LEVEL_DIVIDE) : MAX_LEVEL;
    if ((random_number(2)) && (body.score != 0)) {
        platform_next.radius = MAX_RADIUS - level * RADIUS_DECREASE + random_number(RADIUS_FLOAT);
    } else {
        platform_next.radius = MAX_RADIUS - level * RADIUS_DECREASE - random_number(RADIUS_FLOAT);
    }

    if (random_number(10) == 9) {
        platform_next.type = SCORE_PLATFORM;
    } else if (random_number(10) == 8) {
        platform_next.type = PROPS_PLATFORM;
    } else {
        platform_next.type = NORMAL_PLATFORM;
    }

    platform_next.x = X_BEGIN + platform_current.radius + platform_next.radius + MIN_DISTANCE + random_number(MAX_DISTANCE);
    if (platform_next.x + platform_next.radius >= WINDOW_W) {
        platform_next.x = WINDOW_W - platform_next.radius - 50;
    }
    platform_next.isCircle = random_number(2);
}

void body_jump(unsigned int pressed_time) {
    unsigned int speed = (pressed_time / SPEED_DIVIDE) < MAX_SPEED ? (pressed_time / SPEED_DIVIDE) : MAX_SPEED;
    move_body(speed);
}

void alive_judge() {
    if (body.x + BODY_W / 2 < platform_current.x + platform_current.radius) { //still in current platform
        body.alive = 1;
    } else if ((body.x + BODY_W / 2 > platform_next.x - platform_next.radius) && (body.x + BODY_W / 2 < platform_next.x + platform_next.radius)) { //in next platform
        body.alive = 2;
        body.score++;
        highest_check();
        if (platform_next.type) {
            waiting_counter.write_enable = true; //waiting
            waiting_counter.begin_time = SDL_GetTicks();
        }
        success_audio();
        next_step();
    } else {
        body.alive = 0;
    }
}

void next_step() {
    platform_down();
    copy_platform();
    display_move();
    create_next_platform();
    platform_up();
}

void bonus_check() {
    if (waiting_counter.write_enable && SDL_GetTicks() - waiting_counter.begin_time >= WAITING_TIME) {
        if (platform_current.type == SCORE_PLATFORM) {
            extra_score_audio();
            body.score += 20;
            body.special_score += 20;
            highest_check();
        } else {
            props_audio();
            body.perfect++;
        }
        clear_background();
        keep_platforms();
        draw_body();
        draw_scores();
        anime_refresh(0);
        waiting_counter.write_enable = false; //not waiting
    }
}

void copy_platform() {
    platform_current.x = platform_next.x;
    platform_current.radius = platform_next.radius;
    platform_current.type = platform_next.type;
    platform_current.isCircle = platform_next.isCircle;
}

int random_number(int range) {
    return (rand() % range);
}

void highest_check() {
    if (body.score > app.highest) {
        app.highest = body.score;
    }
}