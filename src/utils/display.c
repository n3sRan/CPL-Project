#include "utils/display.h"

char *score_text;
char *highest_text;
char *perfect_text;

const SDL_Color color_black = {0x00, 0x00, 0x00, 0x00};
const SDL_Color color_red = {0xff, 0x00, 0x00, 0x00};
const SDL_Color color_blue = {0x1e, 0x90, 0xff, 0x00};
const SDL_Color color_green = {0x00, 0xff, 0x00, 0x00};

TTF_Font *font_default;

//Interface
void init_display() {
    app.window = SDL_CreateWindow("Bottle Flip", 100, 100, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);

    font_default = TTF_OpenFont("./res/font/arial.ttf", SCORE_FONT_SIZE);
    puts("Display Init");
}

void quit_display() {
    TTF_CloseFont(font_default);

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    puts("Display Quit");
}


void draw_menu() {
    load_and_draw_img("./res/img/background.jpg", 0, 0);
    load_and_draw_img("./res/img/title.png", 576, 40);
    load_and_draw_img("./res/img/startup.png", 440, 428);
    SDL_RenderPresent(app.renderer);
}

void draw_game_init() {
    clear_background();
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.isCircle); //current
    draw_scores();
    draw_body();
    platform_up(); //next platform
}

void draw_dead_menu() { //文字显示可重整合
    clear_background();
    load_and_draw_text("Game Over", -1, 150, GAME_OVER_FONT_SIZE, color_black);
    body.score = body.score < 9999 ? body.score : 9999;
    score_text = malloc(50);
    sprintf(score_text, "Your score is %d. Your best score is %d.", body.score, app.highest);
    load_and_draw_text(score_text, -1, MIDDLE_Y, SCORE_FONT_SIZE, color_black);
    free(score_text);
    load_and_draw_text("Press Enter to restart.", -1, MIDDLE_Y + 80, SCORE_FONT_SIZE, color_black);
    anime_refresh(600);
}

//Common Functions
void draw_body() {
    load_and_draw_img("./res/img/body1.png",body.x,body.y);
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

void keep_platforms() {
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.isCircle);
    draw_a_platform(platform_next.x, MIDDLE_Y, platform_next.radius, platform_next.type, platform_next.isCircle);
}

void draw_scores() {
    body.score = body.score < 9999 ? body.score : 9999;
    score_text = malloc(20);
    sprintf(score_text, "SCORE: %d", body.score);
    load_and_draw_text(score_text, 50, 30, SCORE_FONT_SIZE, color_black);
    free(score_text);

    app.highest = app.highest < 9999 ? app.highest : 9999;
    highest_text = malloc(20);
    sprintf(highest_text, "HIGHEST: %d", app.highest);
    load_and_draw_text(highest_text, 50, -1, SCORE_FONT_SIZE, color_black);
    free(highest_text);

    body.perfect = body.perfect < 9999 ? body.perfect : 9999;
    perfect_text = malloc(30);
    sprintf(perfect_text, "PERFECT JUMP [ENTER]: %d", body.perfect);
    load_and_draw_text(perfect_text,-2,30,PERFECT_FONT_SIZE,color_black);
    free(perfect_text);
}

void clear_background() {
    SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(app.renderer);
}

//Motion Related
void anime_refresh(unsigned int ms) {
    SDL_RenderPresent(app.renderer);
    if(ms) SDL_Delay(ms);
}

void new_frame(int type,int y){
    clear_background();
    switch (type) {
        case MOVE_BODY:
            keep_platforms();
            break;
        case PLATFORM_UP:
            draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                            platform_current.isCircle);
            draw_a_platform(platform_next.x, y, platform_next.radius, platform_next.type,
                            platform_next.isCircle);
            break;
        case PLATFORM_DOWN:
            draw_a_platform(platform_current.x, y, platform_current.radius, platform_current.type,
                            platform_current.isCircle);
            draw_a_platform(platform_next.x, MIDDLE_Y, platform_next.radius, platform_next.type, platform_next.isCircle);
            break;
        case DISPLAY_MOVE:
            draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type, platform_current.isCircle);
            break;
        default:
            break;
    }
    draw_body();
    draw_scores();
    anime_refresh(REFRESH_TIME);
}

void platform_up() {
    int y = WINDOW_H + platform_next.radius;
    while (y - 20 > MIDDLE_Y) {
        y -= 20;
        new_frame(PLATFORM_UP,y);
    }
    new_frame(MOVE_BODY,-1);
}

void move_body(unsigned int speed) {
    int jump_speed = (int) speed / 2 + 5;
    for (int i = 0; i < 10; ++i) {
        body.y -= jump_speed;
        body.x += (int) speed;
        new_frame(MOVE_BODY,-1);
    }
    for (int i = 0; i < 5; ++i) {
        body.x += (int) speed;
        new_frame(MOVE_BODY,-1);
    }
    for (int i = 0; i < 10; ++i) {
        body.y += jump_speed;
        body.x += (int) speed;
        new_frame(MOVE_BODY,-1);
    }
}

void platform_down() {
    int y = MIDDLE_Y;
    while (y-platform_current.radius-20<WINDOW_H){
        y+=20;
        new_frame(PLATFORM_DOWN,y);
    }
}

void display_move() {
    int pre_body_x = body.x;
    int distance = platform_current.x - X_BEGIN;
    int times = distance / 20;
    for (int i = 1; i <= times; ++i) {
        body.x -= 20;
        platform_current.x -= 20;
        new_frame(DISPLAY_MOVE,-1);
    }
    body.x = pre_body_x - distance;
    platform_current.x = X_BEGIN;
    new_frame(DISPLAY_MOVE,-1);
}

void dead_body() {
    for (int i = 0; i < 10; ++i) {
        body.y += 20;
        new_frame(MOVE_BODY,-1);
    }
    body_spin();
}

void body_spin() {
    body.x -= 40;
    body.y += 40;
    clear_background();
    keep_platforms();
    draw_scores();
    load_and_draw_img("./res/img/body2.png",body.x,body.y);
    anime_refresh(1500);
}

//Basic Functions
void load_and_draw_img(const char *path, int x, int y) {
    SDL_Surface *surface_load = IMG_Load(path);
    SDL_Texture *texture_load = SDL_CreateTextureFromSurface(app.renderer, surface_load);
    SDL_Rect rect_load = {.x =x, .y = y};
    SDL_QueryTexture(texture_load, NULL, NULL, &rect_load.w, &rect_load.h);
    SDL_RenderCopy(app.renderer, texture_load, NULL, &rect_load);
    SDL_FreeSurface(surface_load);
    SDL_DestroyTexture(texture_load);
}

void load_and_draw_text(const char *text, int x, int y, int font_size, SDL_Color font_color) {
    TTF_SetFontSize(font_default, font_size);
    SDL_Surface *surface_text = TTF_RenderText_Blended(font_default, text, font_color);
    SDL_Texture *texture_text = SDL_CreateTextureFromSurface(app.renderer, surface_text);
    SDL_Rect rect_text = {.x = x, .y = y};
    SDL_QueryTexture(texture_text, NULL, NULL, &rect_text.w, &rect_text.h);
    if (x == -1) rect_text.x = WINDOW_W / 2 - rect_text.w / 2; //Middle
    if (x == -2) rect_text.x = WINDOW_W - rect_text.w - 50; //Right
    if (y == -1) rect_text.y = 45 + rect_text.h; //Down Next
    SDL_RenderCopy(app.renderer, texture_text, NULL, &rect_text);
    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture_text);
}

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
