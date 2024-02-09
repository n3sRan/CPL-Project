#include "utils/input.h"

void do_event(SDL_Event event){
    switch (event.type) {
        case SDL_QUIT:
            do_quit(event.quit);
            break;
        case SDL_KEYDOWN:
            do_keydown(event.key);
            break;
        case SDL_KEYUP:
            do_keyup(event.key);
            break;
        default:
            break;
    }
};

static void do_quit(SDL_QuitEvent quit){
    app.keyboard[SDL_SCANCODE_ESCAPE] = true;
}

static void do_keydown(SDL_KeyboardEvent key){
    app.keyboard[key.keysym.scancode]=true;
}

static void do_keyup(SDL_KeyboardEvent key){
    app.keyboard[key.keysym.scancode]=false;
}