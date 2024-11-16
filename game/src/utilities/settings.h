#pragma once
#include <SDL2/SDL_surface.h>

namespace seabattle{
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;
    constexpr float PLAY_FIELD_SIZE = 0.7;
    constexpr int BIG_FONT_SIZE = 35;
    constexpr int MEDIUM_FONT_SIZE = 27;
    constexpr int SMALL_FONT_SIZE = 15;
    constexpr int LOG_LENGTH = 5;
    constexpr int MAX_FIELD_SIZE = 50;
    constexpr const char* FONT_DIR = "../game/assets/fonts/font.ttf";
    constexpr SDL_Color SHIP_SEGMENT_NORMAL = {0, 255, 0, 255};
    constexpr SDL_Color SHIP_SEGMENT_DAMAGED = {255, 128, 0, 255};
    constexpr SDL_Color SHIP_SEGMENT_DESTROYED = {255, 0, 0, 255};
    constexpr SDL_Color CELL_UNKNOWN = {160, 160, 160, 255};
    constexpr SDL_Color CELL_EMPTY = { 96, 133, 233, 255};
    constexpr SDL_Color BACKGROUND_COLOR = {131, 148, 196, 255};
    constexpr SDL_Color POINTER_COLOR = {255, 255, 255, 255};
}