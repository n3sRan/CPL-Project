#ifndef PROJECT_AUDIO_H
#define PROJECT_AUDIO_H

#include "common.h"

void init_audio();

void quit_audio();

void jump_audio_start();
void jump_audio_continue();
void audio_end();

void success_audio();
void fail_audio();
void extra_score_audio();
void props_audio();

#endif //PROJECT_AUDIO_H
