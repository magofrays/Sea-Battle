#ifndef SEABATTLE_GUIDRAWFIELD_H
#define SEABATTLE_GUIDRAWFIELD_H

#include <SDL2/SDL.h>
#include <memory>
#include "../utilities/vector2d.h"
#include "../utilities/settings.h"
#include "../messages/playFieldMessage.h"
#include "../messages/pointerMessage.h"

class GUIDrawField{
    SDL_Renderer * renderer;
    public:
    std::unique_ptr<playFieldMessage> fields[2];
    pointerMessage & pointer;
    GUIDrawField(SDL_Renderer * renderer, pointerMessage & pointer);
    void operator()();
    void setField(std::unique_ptr<playFieldMessage> field);
};

#endif