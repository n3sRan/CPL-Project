#ifndef PROJECT_DISPLAY_H
#define PROJECT_DISPLAY_H

#include "common.h"

#define WINDOW_W 1152
#define WINDOW_H 648

#define SCORE_FONT_SIZE 35
#define PERFECT_FONT_SIZE 25
#define GAME_OVER_FONT_SIZE 120

#define MIDDLE_Y 324
#define X_BEGIN 324

#define LOW_JUMP_SPEED 5
#define MID_JUMP_SPEED 10
#define HIGH_JUMP_SPEED 20
#define JUMP_DIVIDE_ONE 5
#define JUMP_DIVIDE_TWO 15

extern SDL_Texture *texture_title;
extern SDL_Texture *texture_startup;
extern SDL_Texture *texture_background;

extern SDL_Texture *texture_body;
extern SDL_Rect rect_body;

void init_display();
void quit_display();

void draw_menu();

void draw_game_init();

void draw_dead_menu();

void body_init();

void draw_a_platform(int x, int y, int radius, int type, bool isCircle);
void draw_body();
void draw_score();

void keep_background_one();
void keep_background_two();
void clear_background();

void platform_down();
void platform_up();
void display_move();
void move_body(unsigned int speed);
void dead_body();
void body_spin();
void anime_refresh(unsigned int ms);

void DrawSolidCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void DrawSquare(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);



#endif //PROJECT_DISPLAY_H
