#include "utils/audio.h"

Mix_Chunk *jump_begin;
Mix_Chunk *jump_continue;
Mix_Chunk *success;
Mix_Chunk *fail;
Mix_Chunk *score_audio;
Mix_Chunk *props;

void init_audio(){
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,2048);
    jump_begin = Mix_LoadWAV("./res/sound/jump_begin.MP3");
    jump_continue = Mix_LoadWAV("./res/sound/jump_continue.MP3");
    success = Mix_LoadWAV("./res/sound/success.MP3");
    fail = Mix_LoadWAV("./res/sound/fail.MP3");
    score_audio = Mix_LoadWAV("./res/sound/score_audio.MP3");
    props = Mix_LoadWAV("./res/sound/props.MP3");
    puts("Audio Init");
}

void quit_audio(){
    Mix_FreeChunk(jump_begin);
    Mix_FreeChunk(jump_continue);
    Mix_FreeChunk(success);
    Mix_FreeChunk(fail);
    Mix_FreeChunk(score_audio);
    Mix_FreeChunk(props);
    Mix_CloseAudio();
    puts("Audio Quit");
}

void jump_audio_start(){
    Mix_PlayChannel(-1,jump_begin,0);
}

void jump_audio_continue(){
    Mix_PlayChannel(-1,jump_continue,-1);
}

void jump_audio_end(){
    Mix_HaltChannel(-1);
}

void success_audio(){
    Mix_PlayChannel(-1,success,0);
}

void fail_audio(){
    Mix_PlayChannel(-1,fail,0);
}

void extra_score_audio(){
    Mix_PlayChannel(-1,score_audio,0);
}

void props_audio(){
    Mix_PlayChannel(-1,props,0);
}