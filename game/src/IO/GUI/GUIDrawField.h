#ifndef SEABATTLE_GUIDRAWFIELD_H
#define SEABATTLE_GUIDRAWFIELD_H

#include <SDL2/SDL.h>
#include <memory>
#include "../../utilities/vector2d.h"
#include "../../utilities/settings.h"
#include "../../messages/playFieldMessage.h"
#include "../../messages/pointerMessage.h"
#include "GUIDrawText.h"

class GUIDrawField
{
    SDL_Renderer *renderer;
    GUIDrawText *textDrawer;

public:
    std::unique_ptr<playFieldMessage> fields[2];
    std::unique_ptr<pointerMessage> pointer;
    GUIDrawField() = default;
    void operator()();
    void drawOutline(point2d coordinates, point2d size, int size_cell, std::string field_name);
    void drawField(point2d coordinates, point2d size, int size_cell, playField *field, bool fog);
    void drawPointer(point2d coordinates, int size_cell);
    void setField(std::unique_ptr<playFieldMessage> field);
    void setPointer(std::unique_ptr<pointerMessage> pointer);

    void setRenderer(SDL_Renderer *renderer);
    void setTextDrawer(GUIDrawText *textDrawer);
};

#endif