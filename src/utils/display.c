#include "utils/display.h"

SDL_Texture *texture_title;
SDL_Texture *texture_startup;
SDL_Texture *texture_background;
SDL_Texture *texture_over;
SDL_Texture *texture_restart;

SDL_Surface *surface_body;
SDL_Texture *texture_body;
SDL_Rect rect_body;

char score_text[50];
SDL_Surface *surface_score;
SDL_Texture *texture_score;
SDL_Rect rect_score = {50, 30};

char highest_text[20];
SDL_Surface *surface_highest;
SDL_Texture *texture_highest;
SDL_Rect rect_highest = {50};

char perfect_text[30];
SDL_Surface *surface_perfect;
SDL_Texture *texture_perfect;
SDL_Rect rect_perfect = {.y=30};


SDL_Color color_black = {0x00, 0x00, 0x00, 0x00};
SDL_Color color_red = {0xff, 0x00, 0x00, 0x00};
SDL_Color color_blue = {0x1e, 0x90, 0xff, 0x00};
SDL_Color color_green = {0x00, 0xff, 0x00, 0x00};

TTF_Font *font_default;

void init_display() {
    app.window = SDL_CreateWindow("Bottle Flip", 100, 100, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

//    SDL_SetRenderDrawColor(app.renderer, 0x64, 0x95, 0xed, 0xff);
    SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);

    font_default = TTF_OpenFont("./res/font/seguiemj.ttf", SCORE_FONT_SIZE);
}

void quit_display() {
    SDL_FreeSurface(surface_body);
    SDL_DestroyTexture(texture_body);
    SDL_FreeSurface(surface_score);
    SDL_DestroyTexture(texture_score);

    TTF_CloseFont(font_default);

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
}

void draw_menu() {
    SDL_Surface *surface_background = IMG_Load("./res/img/background.jpg");
    texture_background = SDL_CreateTextureFromSurface(app.renderer, surface_background);
    SDL_Rect rect_background = {.x=0, .y=0};
    SDL_QueryTexture(texture_background, NULL, NULL, &rect_background.w, &rect_background.h);
    SDL_RenderCopy(app.renderer, texture_background, NULL, &rect_background);

    SDL_Surface *surface_title = IMG_Load("./res/img/title.png");
    texture_title = SDL_CreateTextureFromSurface(app.renderer, surface_title);
    SDL_Rect rect_title = {.x=576, .y=40};
    SDL_QueryTexture(texture_title, NULL, NULL, &rect_title.w, &rect_title.h);
    SDL_RenderCopy(app.renderer, texture_title, NULL, &rect_title);

    SDL_Surface *surface_startup = IMG_Load("./res/img/startup.png");
    texture_startup = SDL_CreateTextureFromSurface(app.renderer, surface_startup);
    SDL_Rect rect_startup = {.x=440, .y=428};
    SDL_QueryTexture(texture_startup, NULL, NULL, &rect_startup.w, &rect_startup.h);
    SDL_RenderCopy(app.renderer, texture_startup, NULL, &rect_startup);

    SDL_RenderPresent(app.renderer);

    SDL_FreeSurface(surface_startup);
    SDL_DestroyTexture(texture_startup);
    SDL_FreeSurface(surface_title);
    SDL_DestroyTexture(texture_title);
    SDL_FreeSurface(surface_background);
    SDL_DestroyTexture(texture_background);
}

void draw_game_init() {
    clear_background();
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.isCircle); //current
    draw_score();
    body_init();
    draw_body();
    platform_up(); //next
    SDL_RenderPresent(app.renderer);
}

void draw_dead_menu() { //文字显示可重整合
    clear_background();
    TTF_SetFontSize(font_default, GAME_OVER_FONT_SIZE);
    SDL_Surface *surface_over = TTF_RenderText_Blended(font_default, "Game Over", color_black);
    texture_over = SDL_CreateTextureFromSurface(app.renderer, surface_over);
    SDL_Rect rect_over = {.y = 150};
    SDL_QueryTexture(texture_over, NULL, NULL, &rect_over.w, &rect_over.h);
    rect_over.x = WINDOW_W / 2 - rect_over.w / 2;
    SDL_RenderCopy(app.renderer, texture_over, NULL, &rect_over);

    TTF_SetFontSize(font_default, SCORE_FONT_SIZE);
    body.score = body.score < 9999 ? body.score : 9999;
    sprintf(score_text, "Your score is %d. Your best score is %d.", body.score, app.highest);
    SDL_Rect rect_dead_score={.y = MIDDLE_Y};
    surface_score = TTF_RenderText_Blended(font_default, score_text, color_black);
    texture_score = SDL_CreateTextureFromSurface(app.renderer, surface_score);
    SDL_QueryTexture(texture_score, NULL, NULL, &rect_dead_score.w, &rect_dead_score.h);
    rect_dead_score.x = WINDOW_W/2 -rect_dead_score.w/2;
    SDL_RenderCopy(app.renderer, texture_score, NULL, &rect_dead_score);

    SDL_Surface *surface_restart = TTF_RenderText_Blended(font_default,"Press Enter to restart.",color_black);
    texture_restart = SDL_CreateTextureFromSurface(app.renderer,surface_restart);
    SDL_Rect rect_restart = {.y = MIDDLE_Y+80};
    SDL_QueryTexture(texture_restart,NULL,NULL,&rect_restart.w,&rect_restart.h);
    rect_restart.x = WINDOW_W/2-rect_restart.w/2;
    SDL_RenderCopy(app.renderer,texture_restart,NULL,&rect_restart);

    SDL_RenderPresent(app.renderer);
    SDL_Delay(1000);

    SDL_FreeSurface(surface_over);
    SDL_DestroyTexture(texture_over);
    SDL_FreeSurface(surface_restart);
    SDL_DestroyTexture(texture_restart);
}

//Common
void body_init() {
    surface_body = IMG_Load("./res/img/body1.png");
    texture_body = SDL_CreateTextureFromSurface(app.renderer, surface_body);
    SDL_QueryTexture(texture_body, NULL, NULL, &rect_body.w, &rect_body.h);
    rect_body.x = body.x;
    rect_body.y = body.y;
}

void draw_a_platform(int x, int y, int radius, int type, bool isCircle) {
    SDL_Color platform_color;
    switch (type) {
        case 0:
            platform_color = color_blue;
            break;
        case 1:
            platform_color = color_red;
            break;
        default:
            platform_color = color_green;
            break;
    }
    if (isCircle) {
        DrawSolidCircle(app.renderer, x, y, radius, platform_color);
    } else {
        DrawSquare(app.renderer, x, y, radius, platform_color);
    }
}

void draw_body() {
    SDL_RenderCopy(app.renderer, texture_body, NULL, &rect_body);
}

void draw_score() {
    TTF_SetFontSize(font_default,SCORE_FONT_SIZE);
    body.score = body.score < 9999 ? body.score : 9999;
    TTF_SetFontSize(font_default, SCORE_FONT_SIZE);
    sprintf(score_text, "SCORE: %d", body.score);
    surface_score = TTF_RenderText_Blended(font_default, score_text, color_black);
    texture_score = SDL_CreateTextureFromSurface(app.renderer, surface_score);
    SDL_QueryTexture(texture_score, NULL, NULL, &rect_score.w, &rect_score.h);
    SDL_RenderCopy(app.renderer, texture_score, NULL, &rect_score);

    app.highest = app.highest<9999?app.highest:9999;
    sprintf(highest_text,"HIGHEST: %d",app.highest);
    surface_highest = TTF_RenderText_Blended(font_default,highest_text,color_black);
    texture_highest = SDL_CreateTextureFromSurface(app.renderer,surface_highest);
    SDL_QueryTexture(texture_highest,NULL,NULL,&rect_highest.w,&rect_highest.h);
    rect_highest.y = 45+rect_score.h;
    SDL_RenderCopy(app.renderer,texture_highest,NULL,&rect_highest);

    TTF_SetFontSize(font_default,PERFECT_FONT_SIZE);
    sprintf(perfect_text,"PERFECT JUMP [ENTER]: %d",body.perfect);
    surface_perfect = TTF_RenderText_Blended(font_default,perfect_text,color_black);
    texture_perfect  = SDL_CreateTextureFromSurface(app.renderer,surface_perfect);
    SDL_QueryTexture(texture_perfect,NULL,NULL,&rect_perfect.w,&rect_perfect.h);
    rect_perfect.x = WINDOW_W-50-rect_perfect.w;
    SDL_RenderCopy(app.renderer,texture_perfect,NULL,&rect_perfect);
}

void keep_background_one() { //keep background and move body
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.isCircle);
    draw_a_platform(platform_next.x, MIDDLE_Y, platform_next.radius, platform_next.type, platform_next.isCircle);
    draw_body();
    draw_score();
    anime_refresh(40);
}

void keep_background_two() { //only exist current platform and body
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.isCircle);
    draw_body();
    draw_score();
    anime_refresh(20);
}

void clear_background() {
    SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(app.renderer);
}

//Motion related
void anime_refresh(unsigned int ms) {
    SDL_RenderPresent(app.renderer);
    SDL_Delay(ms);
}

void platform_down() {
    for (int i = 1; MIDDLE_Y - platform_current.radius + 20 * (i - 1) < WINDOW_H; ++i) {
        clear_background();
        draw_a_platform(platform_current.x, MIDDLE_Y + 20 * i, platform_current.radius, platform_current.type,
                        platform_current.isCircle); //current platform down
        draw_a_platform(platform_next.x, MIDDLE_Y, platform_next.radius, platform_next.type, platform_next.isCircle);
        draw_body();
        draw_score();
        anime_refresh(20);
    }
}

void platform_up() {
    int y = WINDOW_H + platform_next.radius;
    while (y - 20 > MIDDLE_Y) {
        y -= 20;
        clear_background();
        draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                        platform_current.isCircle);
        draw_a_platform(platform_next.x, y, platform_next.radius, platform_next.type,
                        platform_next.isCircle); //next platform up
        draw_body();
        draw_score();
        anime_refresh(20);
    }
    clear_background();
    keep_background_one();
}

void display_move() {
    int distance = platform_current.x - X_BEGIN;
    int times = distance / 20;
    for (int i = 1; i <= times; ++i) {
        clear_background();
        //moving display
        rect_body.x -= 20;
        platform_current.x -= 20;
        //draw current platform and body
        keep_background_two();
    }
    clear_background();
    //move to right location
    rect_body.x = body.x - distance;
    platform_current.x = X_BEGIN;
    body.x = rect_body.x;
    //draw current platform and body
    keep_background_two();
}

void move_body(unsigned int speed) {
    int jump_speed;
    if(speed<=JUMP_DIVIDE_ONE){
        jump_speed=LOW_JUMP_SPEED;
    }else if(speed<=JUMP_DIVIDE_TWO){
        jump_speed = MID_JUMP_SPEED;
    }else{
        jump_speed = HIGH_JUMP_SPEED;
    }
    for (int i = 0; i < 10; ++i) {
        clear_background();
        rect_body.y -= jump_speed;
        rect_body.x += (int) speed;
        keep_background_one();
    }
    for (int i = 0; i < 5; ++i) {
        clear_background();
        rect_body.x += (int) speed;
        keep_background_one();
    }
    for (int i = 0; i < 10; ++i) {
        clear_background();
        rect_body.y += jump_speed;
        rect_body.x += (int) speed;
        keep_background_one();
    }
    body.x = rect_body.x;
}

void dead_body() {
    for (int i = 0; i < 10; ++i) {
        clear_background();
        rect_body.y += 20;
        keep_background_one();
        SDL_Delay(20);
    }
    body_spin();
}

void body_spin() {
    surface_body = IMG_Load("./res/img/body2.png");
    texture_body = SDL_CreateTextureFromSurface(app.renderer, surface_body);
    SDL_QueryTexture(texture_body, NULL, NULL, &rect_body.w, &rect_body.h);
    rect_body.x -= 40;
    rect_body.y += 40;
    clear_background();
    keep_background_one();
}

//Basic functions
void DrawSolidCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void DrawSquare(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect FillRect = {x - radius, y - radius, radius * 2, radius * 2};
    SDL_RenderFillRect(renderer, &FillRect);
}