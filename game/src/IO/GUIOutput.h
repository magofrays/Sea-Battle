#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gameOutput.h"
#include "../utilities/settings.h"

class GUIOutput : public gameOutput{
    SDL_Window * window;
    SDL_Renderer * renderer;
    public:
        GUIOutput();
        void drawField(point2d coordinates, playField & field);
        void drawPointer(point2d & pointer);
        void drawText(std::string text);
        ~GUIOutput();

        template <typename T>
        void Handle(Message<T> message);
};