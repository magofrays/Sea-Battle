#ifndef SEABATTLE_GUIOUTPUT_H
#define SEABATTLE_GUIOUTPUT_H

#include "../messages/messageHandler.h"

#include "../messages/textMessage.h"
#include "../messages/playFieldMessage.h"
#include "../messages/pointerMessage.h"
#include "../utilities/settings.h"

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
    std::vector<std::string> instructions;
    textMessage log[seabattle::LOG_LENGTH];
    pointerMessage pointer; 
    
    messageHandler * handler = nullptr;
    
    public:
        GUIOutput();
        void drawField(std::string field_name, playField & field, fieldPosition position, bool fog, bool draw_pointer=false);
        
        void drawPointer(int size_cell, point2d coordinates, point2d field_size);


        SDL_Rect drawText(std::string text, point2d coordinates, fontSize font_size, 
                    SDL_Color color = {255, 255, 255, 255}, bool is_centered = false);
        
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
