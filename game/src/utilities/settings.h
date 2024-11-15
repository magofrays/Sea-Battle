#pragma once
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>

namespace seabattle{
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 600;
    constexpr float PLAY_FIELD_SIZE = 0.7;
    constexpr int TITLE_FONT_SIZE = 35;
    constexpr int LOG_FONT_SIZE = 20;
    constexpr int LOG_LENGTH = 5;
    constexpr int FIELD_FONT_SIZE = 30;
    constexpr int MAX_FIELD_SIZE = 10;
    constexpr const char* FONT_DIR = "../assets/fonts/font.ttf";
    constexpr SDL_Color SHIP_SEGMENT_NORMAL = {0, 255, 0, 255};
    constexpr SDL_Color SHIP_SEGMENT_DAMAGED = {255, 128, 0, 255};
    constexpr SDL_Color SHIP_SEGMENT_DESTROYED = {255, 0, 0, 255};
    constexpr SDL_Color CELL_UNKNOWN = {160, 160, 160, 255};
    constexpr SDL_Color CELL_EMPTY = { 96, 133, 233, 255};
    constexpr SDL_Color BACKGROUND_COLOR = {131, 148, 196, 255};
}