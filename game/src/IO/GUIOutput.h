#ifndef SEABATTLE_GUIOUTPUT_H
#define SEABATTLE_GUIOUTPUT_H

#include "../messages/messageHandler.h"

#include "../messages/textMessage.h"
#include "../messages/playFieldMessage.h"
#include "../messages/pointerMessage.h"
#include "../utilities/settings.h"
#include "GUIDrawField.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class GUIOutput : public messageHandler{
    enum fontSize{
        big, medium, small
    };
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font * big_font;
    TTF_Font * medium_font;
    TTF_Font * small_font;
    textMessage title;
    textMessage log[seabattle::LOG_LENGTH];
    pointerMessage pointer;
    GUIDrawField fieldDrawer;
    
    
    messageHandler * handler = nullptr;
    
    public:
        GUIOutput();

        SDL_Color enumToColor(textColor color);

        SDL_Rect drawText(std::string text, point2d coordinates, SDL_Color color, fontSize font_size, bool is_centered = false);
        
        void redirectText(textMessage text);

        void drawTitle();
        void drawInstructions();
        void drawLog();

        ~GUIOutput();

        void Handle(std::unique_ptr<Message> message);

        void update();
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};

#endif
