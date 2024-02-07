#ifndef PROJECT_INPUT_H
#define PROJECT_INPUT_H

#include "common.h"

void do_event(SDL_Event event);

static void do_quit(SDL_QuitEvent quit);
static void do_keydown(SDL_KeyboardEvent key);
static void do_keyup(SDL_KeyboardEvent key);

#endif //PROJECT_INPUT_H
