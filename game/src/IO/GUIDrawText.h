#ifndef SEABATTLE_GUIDRAWTEXT_H
#define SEABATTLE_GUIDRAWTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "../utilities/vector2d.h"
#include "../utilities/settings.h"
#include "../messages/textMessage.h"

class GUIDrawText{
    SDL_Renderer * renderer;
    TTF_Font * big_font;
    TTF_Font * medium_font;
    TTF_Font * small_font;
    textMessage title;
    textMessage log[seabattle::LOG_LENGTH];
    public:
        enum fontSize {big, medium, small};
        GUIDrawText();
        SDL_Color enumToColor(textColor color);
        SDL_Rect drawText(std::string text, point2d coordinates, SDL_Color color, fontSize font_size, bool is_centered = false);
        void redirectText(textMessage text);
        void drawTitle();
        void drawLog();
        void operator()();

        void setRenderer(SDL_Renderer * renderer);
        ~GUIDrawText();
};

#endif