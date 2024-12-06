#ifndef SEABATTLE_SETTINGS_H
#define SEABATTLE_SETTINGS_H

#include <SDL2/SDL.h>

namespace seabattle{
    constexpr int WIDTH = 1600;
    constexpr int HEIGHT = 900;
    constexpr float PLAY_FIELD_SIZE = 0.7;
    constexpr int BIG_FONT_SIZE = 35;
    constexpr int MEDIUM_FONT_SIZE = 27;
    constexpr int SMALL_FONT_SIZE = 15;
    constexpr int LOG_LENGTH = 7;
    constexpr int MAX_FIELD_SIZE = 20;
    static const char* FONT_DIR = "../game/assets/fonts/font.ttf";
    constexpr SDL_Color SHIP_SEGMENT_NORMAL = {0, 255, 0, 255};
    constexpr SDL_Color SHIP_SEGMENT_DAMAGED = {255, 128, 0, 255};
    constexpr SDL_Color SHIP_SEGMENT_DESTROYED = {255, 0, 0, 255};
    constexpr SDL_Color CELL_UNKNOWN = {160, 160, 160, 255};
    constexpr SDL_Color CELL_EMPTY = { 96, 133, 233, 255};
    constexpr SDL_Color CELL_ATTACKED = {66, 103, 203, 255};
    constexpr SDL_Color BACKGROUND_COLOR = {131, 148, 196, 255};
    constexpr SDL_Color POINTER_COLOR = {255, 255, 255, 200};
    static const char * SAVE_DIR = "../game/data/save.json";
    static const char * CONTROL_DIR = "../game/data/Nastya_control.json";
}

#endif