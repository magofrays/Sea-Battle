#include "GUIOutput.h"
#include <iostream>

GUIOutput::GUIOutput(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
    std::cout << "Created SDL\n";
    window = SDL_CreateWindow("Sea Battle",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    seabattle::WIDTH, seabattle::HEIGHT,
                                    SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 131, 148, 196, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    textDrawer.setRenderer(renderer);
    fieldDrawer.setRenderer(renderer);
    fieldDrawer.setTextDrawer(&textDrawer);
}


void GUIOutput::update(){
    SDL_Color c = seabattle::BACKGROUND_COLOR;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(renderer);
    this->textDrawer();
    this->fieldDrawer();
    SDL_RenderPresent(renderer);
}

void GUIOutput::sendText(std::unique_ptr<textMessage> text){
    textDrawer.redirectText(*text);
}

void GUIOutput::sendField(std::unique_ptr<playFieldMessage> field){
    fieldDrawer.setField(std::move(field));
}

void GUIOutput::sendPointer(std::unique_ptr<pointerMessage> pointer){
    fieldDrawer.setPointer(std::move(pointer));
}

GUIOutput::~GUIOutput(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
