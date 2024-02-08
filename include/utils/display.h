#ifndef PROJECT_DISPLAY_H
#define PROJECT_DISPLAY_H

#include "common.h"

#define WINDOW_W 1152
#define WINDOW_H 648

#define SCORE_FONT_SIZE 27
#define PERFECT_FONT_SIZE 27
#define GAME_OVER_FONT_SIZE 120

#define REFRESH_TIME 17
#define DEAD_REFRESH_TIME 34

#define MIDDLE_Y 324
#define X_BEGIN 324

#define MOVE_BODY 0
#define PLATFORM_UP 1
#define PLATFORM_DOWN 2
#define DISPLAY_MOVE 3

void init_display();
void quit_display();

void draw_menu();
void draw_game_init();
void draw_dead_menu();

void draw_body(int status);
void draw_a_platform(int x, int y, int radius, int type, int shape);
void keep_platforms();
void draw_scores();
void clear_background();

void anime_refresh(unsigned int ms);
void new_frame(int type,int y,int status,int delay);
void draw_speed(unsigned int temp_time,bool refresh);
void platform_down();
void platform_up();
void display_move();
void move_body(unsigned int speed);
void body_dead();
void body_spin();

void load_and_draw_img(const char* path, int x, int y);
void load_and_draw_text(const char *text,int x,int y,int font_size,SDL_Color font_color);
void DrawFilledCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void DrawFilledSquare(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void DrawFilledHexagon(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);

#endif //PROJECT_DISPLAY_H
