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
    app.window = SDL_CreateWindow("Jumper", 100, 100, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
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
    load_and_draw_img("./res/img/title.png", 600, 40);
    load_and_draw_img("./res/img/startup.png", 440, 428);
    SDL_RenderPresent(app.renderer);
}

void draw_game_init() {
    clear_background();
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.shape); //current
    draw_scores();
    draw_body(0);
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
void draw_body(int status) {
    switch (status) {
        case 0:
            load_and_draw_img("./res/img/body.png",body.x,body.y);
            return;
        case 1:
            load_and_draw_img("./res/img/body_move.png",body.x,body.y);
            return;
        case 2:
            load_and_draw_img("./res/img/body_bonus.png",body.x,body.y);
            return;
        default:
            return;
    }
}

void draw_a_platform(int x, int y, int radius, int type, int shape) {
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
    if (shape==CIRCLE) {
        DrawFilledCircle(app.renderer, x, y, radius, platform_color);
    } else if(shape==SQUARE) {
        DrawFilledSquare(app.renderer, x, y, radius, platform_color);
    } else if(shape==HEXAGON){
        DrawFilledHexagon(app.renderer,x,y,radius,platform_color);
    }
}

void keep_platforms() {
    draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                    platform_current.shape);
    draw_a_platform(platform_next.x, MIDDLE_Y, platform_next.radius, platform_next.type, platform_next.shape);
}

void draw_scores() {
    body.score = body.score < 9999 ? body.score : 9999;
    score_text = malloc(20);
    sprintf(score_text, "SCORE: %d", body.score);
    load_and_draw_text(score_text, 30, 20, SCORE_FONT_SIZE, color_black);
    free(score_text);

    app.highest = app.highest < 9999 ? app.highest : 9999;
    highest_text = malloc(20);
    sprintf(highest_text, "HIGHEST: %d", app.highest);
    load_and_draw_text(highest_text, 30, -1, SCORE_FONT_SIZE, color_black);
    free(highest_text);

    body.perfect = body.perfect < 9999 ? body.perfect : 9999;
    perfect_text = malloc(30);
    sprintf(perfect_text, "PERFECT JUMP [ENTER]: %d", body.perfect);
    load_and_draw_text(perfect_text,-2,20,PERFECT_FONT_SIZE,color_black);
    free(perfect_text);

    draw_speed(0,false);
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

void new_frame(int type,int y,int status,int delay){
    clear_background();
    switch (type) {
        case MOVE_BODY:
            keep_platforms();
            break;
        case MOVE_BODY_BONUS:
            keep_platforms();
            load_and_draw_img("./res/img/bonus.png",210,25);
            break;
        case PLATFORM_UP:
            draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type,
                            platform_current.shape);
            draw_a_platform(platform_next.x, y, platform_next.radius, platform_next.type,
                            platform_next.shape);
            break;
        case PLATFORM_DOWN:
            draw_a_platform(platform_current.x, y, platform_current.radius, platform_current.type,
                            platform_current.shape);
            draw_a_platform(platform_next.x, MIDDLE_Y, platform_next.radius, platform_next.type, platform_next.shape);
            break;
        case DISPLAY_MOVE:
            draw_a_platform(platform_current.x, MIDDLE_Y, platform_current.radius, platform_current.type, platform_current.shape);
            break;
        default:
            break;
    }
    draw_body(status);
    draw_scores();
    anime_refresh(delay);
}

void draw_speed(unsigned int temp_time,bool refresh){
    SDL_SetRenderDrawColor(app.renderer,0x00, 0x00, 0x00, 0x00);
    SDL_Rect rect_speed_framework = {30, 95, 150, 15};
    SDL_RenderDrawRect(app.renderer,&rect_speed_framework);

    temp_time = temp_time<=2000?temp_time:2000;
    double speed_length = temp_time/2000.0*150.0;
    SDL_Rect rect_speed = {30, 95, (int)speed_length, 15};
    SDL_RenderFillRect(app.renderer,&rect_speed);
    if(refresh) anime_refresh(0);
}

void platform_up() {
    int y = WINDOW_H + platform_next.radius;
    while (y - 20 > MIDDLE_Y) {
        y -= 20;
        new_frame(PLATFORM_UP,y,0,REFRESH_TIME);
    }
    new_frame(MOVE_BODY,-1,0,REFRESH_TIME);
}

void move_body(unsigned int speed) {
    int jump_speed = (int) speed / 2 + 5;
    for (int i = 0; i < 10; ++i) {
        body.y -= jump_speed;
        body.x += (int) speed;
        new_frame(MOVE_BODY,-1,0,REFRESH_TIME);
    }
    for (int i = 0; i < 5; ++i) {
        body.x += (int) speed;
        new_frame(MOVE_BODY,-1,0,REFRESH_TIME);
    }
    for (int i = 0; i < 10; ++i) {
        body.y += jump_speed;
        body.x += (int) speed;
        new_frame(MOVE_BODY,-1,0,REFRESH_TIME);
    }
}

void platform_down() {
    int y = MIDDLE_Y;
    while (y-platform_current.radius-20<WINDOW_H){
        y+=20;
        new_frame(PLATFORM_DOWN,y,0,REFRESH_TIME);
    }
}

void display_move() {
    int pre_body_x = body.x;
    int distance = platform_current.x - X_BEGIN;
    int times = distance / 20;
    for (int i = 1; i <= times; ++i) {
        body.x -= 20;
        platform_current.x -= 20;
        new_frame(DISPLAY_MOVE,-1,0,REFRESH_TIME);
    }
    body.x = pre_body_x - distance;
    platform_current.x = X_BEGIN;
    new_frame(DISPLAY_MOVE,-1,0,REFRESH_TIME);
}

void body_dead() {
    for (int i = 0; i < 10; ++i) {
        body.y += 20;
        new_frame(MOVE_BODY,-1,1,DEAD_REFRESH_TIME);
    }
    anime_refresh(500);
    body_spin();
}

void body_spin() {
    body.x -= 40;
    body.y += 40;
    clear_background();
    keep_platforms();
    draw_scores();
    load_and_draw_img("./res/img/body_dead.png",body.x,body.y);
    anime_refresh(500);
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
    if (y == -1) rect_text.y = 25 + rect_text.h; //Down Next
    SDL_RenderCopy(app.renderer, texture_text, NULL, &rect_text);
    SDL_FreeSurface(surface_text);
    SDL_DestroyTexture(texture_text);
}

void DrawFilledCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
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

void DrawFilledSquare(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect FillRect = {x - radius, y - radius, radius * 2, radius * 2};
    SDL_RenderFillRect(renderer, &FillRect);
}

void DrawFilledHexagon(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // Calculate
    int num_vertices = 6;
    double angle = M_PI / 3;
    SDL_Point *vertices = malloc(6*sizeof(SDL_Point));
    for (int i = 0; i < num_vertices; ++i) {
        vertices[i].x = x + radius * cos(i * angle);
        vertices[i].y = y + radius * sin(i * angle);
    }
    // Lines
    for (int i = 0; i < num_vertices; ++i) {
        SDL_RenderDrawLine(renderer, vertices[i].x, vertices[i].y, vertices[(i + 1) % num_vertices].x, vertices[(i + 1) % num_vertices].y);
    }
    // Fill
    int min_x = x - radius;
    int max_x = x + radius;
    int min_y = y - radius;
    int max_y = y + radius;
    for (int curr_x = min_x; curr_x <= max_x; ++curr_x) {
        for (int curr_y = min_y; curr_y <= max_y; ++curr_y) {
            // Check
            int i, j, c = 0;
            for (i = 0, j = num_vertices - 1; i < num_vertices; j = i++) {
                if (((vertices[i].y > curr_y) != (vertices[j].y > curr_y)) &&
                    (curr_x < (vertices[j].x - vertices[i].x) * (curr_y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
                    c = !c;
            }
            if (c) {
                SDL_RenderDrawPoint(renderer, curr_x, curr_y);
            }
        }
    }
    free(vertices);
}
