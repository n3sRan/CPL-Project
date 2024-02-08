//
// Created by n3sRa on 2024/1/23.
//

#ifndef PROJECT_COMMON_H
#define PROJECT_COMMON_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "math.h"

#define HANDLE_ERROR(msg) printf(msg ": %s\n",SDL_GetError()); \
    exit(EXIT_FAILURE);


#define BODY_W 80
#define BODY_H 120

#define MIN_DISTANCE 100
#define MAX_DISTANCE 300

#define SQUARE 0
#define CIRCLE 1
#define HEXAGON 2

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int gaming;
    int highest;
    bool *keyboard;

} App;

typedef struct {
    int x;
    int y;
    int score;
    int special_score;
    int perfect;
    int alive; //0:dead, 1:current, 2:next
}Body;

typedef struct {
    int x;
    int radius;
    int type; // {0, 1, 2}
    int shape;
}Platform;

extern App app;

extern Body body;

extern Platform platform_current;

extern Platform platform_next;

#endif //PROJECT_COMMON_H
