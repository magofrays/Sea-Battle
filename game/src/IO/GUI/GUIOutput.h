#ifndef SEABATTLE_GUIOUTPUT_H
#define SEABATTLE_GUIOUTPUT_H

#include "../../messages/textMessage.h"
#include "../../messages/playFieldMessage.h"
#include "../../messages/pointerMessage.h"
#include "../../utilities/settings.h"
#include "GUIDrawField.h"
#include "GUIDrawText.h"

#include <SDL2/SDL.h>

class GUIOutput
{

    SDL_Window *window;
    SDL_Renderer *renderer;

    GUIDrawText textDrawer;
    GUIDrawField fieldDrawer;

public:
    GUIOutput();
    void update();
    void sendText(std::unique_ptr<textMessage> text);
    void sendField(std::unique_ptr<playFieldMessage> field);
    void sendPointer(std::unique_ptr<pointerMessage> pointer);
    ~GUIOutput();
};

#endif
