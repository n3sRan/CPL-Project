cmake_minimum_required(VERSION 3.27)
project(Project C)

set(CMAKE_C_STANDARD 17)

#add_compile_definitions(AUDIO_OFF)

include_directories(include)
add_executable(Project
        main.c
        game.c
        utils/display.c
        utils/audio.c
        utils/input.c
)

target_link_libraries(Project PRIVATE
        mingw32
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)
