#ifndef SEABATTLE_GUIOUTPUT_H
#define SEABATTLE_GUIOUTPUT_H

#include "../messages/messageHandler.h"

#include "../messages/textMessage.h"
#include "../messages/playFieldMessage.h"
#include "../messages/pointerMessage.h"
#include "../utilities/settings.h"
#include "GUIDrawField.h"
#include "GUIDrawText.h"

#include <SDL2/SDL.h>


class GUIOutput : public messageHandler{

    SDL_Window * window;
    SDL_Renderer * renderer;
    
    GUIDrawText textDrawer;
    GUIDrawField fieldDrawer;
    
    messageHandler * handler = nullptr;
    
    public:
        GUIOutput();

        void update();
        
        ~GUIOutput();

        void Handle(std::unique_ptr<Message> message);

        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};

#endif
