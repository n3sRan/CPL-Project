#ifndef PROJECT_DISPLAY_H
#define PROJECT_DISPLAY_H

#include "common.h"

#define WINDOW_W 1152
#define WINDOW_H 648

#define SCORE_FONT_SIZE 35
#define PERFECT_FONT_SIZE 25
#define GAME_OVER_FONT_SIZE 120

#define REFRESH_TIME 17
#define DEAD_REFRESH_TIME 30

#define MIDDLE_Y 324
#define X_BEGIN 324

#define MOVE_BODY 0
#define PLATFORM_UP 1
#define PLATFORM_DOWN 2
#define DISPLAY_MOVE 3



extern SDL_Surface *surface_body;
extern SDL_Texture *texture_body;
extern SDL_Rect rect_body;

void init_display();
void quit_display();

void draw_menu();
void draw_game_init();
void draw_dead_menu();

void draw_body();
void draw_a_platform(int x, int y, int radius, int type, bool isCircle);
void keep_platforms();
void draw_scores();
void clear_background();

void anime_refresh(unsigned int ms);
void new_frame(int type,int y);
void platform_down();
void platform_up();
void display_move();
void move_body(unsigned int speed);
void dead_body();
void body_spin();

void load_and_draw_img(const char* path, int x, int y);
void load_and_draw_text(const char *text,int x,int y,int font_size,SDL_Color font_color);
void DrawSolidCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);
void DrawSquare(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color);

#endif //PROJECT_DISPLAY_H
