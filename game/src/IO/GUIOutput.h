#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gameOutput.h"
#include "../utilities/settings.h"
#include "../utilities/vector2d.h"

class GUIOutput : public gameOutput{
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font* font;
    public:
        GUIOutput();
        void drawField(playField & field);
        void drawPointer(point2d & pointer){}
        void drawText(point2d coors, std::string text);
        ~GUIOutput();

        void Handle(std::unique_ptr<Message> message);
};