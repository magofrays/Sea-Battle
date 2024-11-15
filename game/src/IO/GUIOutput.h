#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gameOutput.h"
#include "../utilities/settings.h"
#include "../utilities/vector2d.h"

class GUIOutput : public gameOutput{ //need fix for fonts program is slow
    SDL_Window * window;
    SDL_Renderer * renderer;
    Text title;
    std::vector<std::string> instructions;
    Text log[seabattle::LOG_LENGTH];
    pointerMessage pointer; 

    public:
        GUIOutput();
        void drawField(std::string field_name, playField & field, fieldPosition position, bool fog, bool draw_pointer=false);
        
        void drawPointer(int size_cell, point2d coordinates);


        SDL_Rect drawText(std::string text, point2d coordinates, int font_size, 
                    SDL_Color color = {255, 255, 255, 255}, bool is_centered = false);
        
        void redirectText(Text text, textPosition position);

        void drawTitle();
        //void drawInstructions();
        void drawLog();
        
        void transformPointer(std::unique_ptr<pointerMessage> pointer){
            this->pointer = *pointer;
            pointer.info //утро вечера мудренее
        }

        ~GUIOutput();

        void Handle(std::unique_ptr<Message> message);

        void update();
};
