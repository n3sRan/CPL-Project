#include "main.h"

App app = {.gaming = 0, .highest = 0};

int main(int argc, char *argv[]) {
    init_app();

    do_menu_logic();

    while (app.gaming) {
        if (app.gaming == 1) do_game_logic();
        if (app.gaming == 2) do_dead_logic();
        if (app.gaming == 0)break;
    }

    quit_app();
    return 0;
}


static void init_app() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        HANDLE_ERROR("Init SDL");
    }
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        HANDLE_ERROR("Init Image");
    }
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)) {
        HANDLE_ERROR("Init Mixer")
    }
    if (TTF_Init() == -1) {
        HANDLE_ERROR("Init TTF")
    }
    puts("App Init");

    init_keyboard();
    init_display();
    init_audio();
}

static void quit_app() {
    quit_audio();
    quit_display();
    quit_keyboard();

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    puts("App Quit");
}

static void init_keyboard() {
    app.keyboard = calloc(SDL_NUM_SCANCODES, sizeof(bool));
    if(app.keyboard) puts("Keyboard Init");
}

static void quit_keyboard() {
    free(app.keyboard);
    puts("Keyboard Quit");
}