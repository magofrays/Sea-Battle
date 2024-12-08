#include "GUIDrawText.h"
#include <iostream>

GUIDrawText::GUIDrawText(){
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
    }
    std::cout << "Created TTF\n";
    big_font = TTF_OpenFont(seabattle::FONT_DIR, seabattle::BIG_FONT_SIZE);
    if (big_font == nullptr) {
        std::cerr << TTF_GetError() << std::endl;
        throw std::runtime_error("Failed to create font");
    }
    medium_font = TTF_OpenFont(seabattle::FONT_DIR, seabattle::MEDIUM_FONT_SIZE);
    if (medium_font == nullptr) {
        std::cerr << TTF_GetError() << std::endl;
        throw std::runtime_error("Failed to create font");
    }
    small_font = TTF_OpenFont(seabattle::FONT_DIR, seabattle::SMALL_FONT_SIZE);
    if (small_font == nullptr) {
        std::cerr << TTF_GetError() << std::endl;
        throw std::runtime_error("Failed to create font");
    }
}

SDL_Color GUIDrawText::enumToColor(textColor color){
    switch(color){
        case textColor::green:
            return {0, 255, 0};
        case textColor::red:
            return {255, 0, 0};
        case textColor::yellow:
            return {255, 255, 0};
        case textColor::white:
            return {255, 255, 255};
        case textColor::purple:
            return {255, 0, 255};
        case textColor::blue:
            return {0, 0, 255};
        case textColor::black:
            return {0, 0, 0};
        default:
            return {255, 255, 255};
    }
}

SDL_Rect GUIDrawText::drawText(std::string text, point2d coordinates, SDL_Color color, fontSize font_size, bool is_centered){
    TTF_Font * font;
    switch(font_size){
        case big:
            font = big_font;
            break;
        case medium:
            font = medium_font;
            break;
        case small:
            font = small_font;
    }
    if(text.size() != 0){
        
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (textSurface == nullptr) {
            std::cerr << TTF_GetError() << std::endl;
            throw std::runtime_error("Failed to create text surface");
        }
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == nullptr) {
            std::cerr << TTF_GetError() << std::endl;
            throw std::runtime_error("Failed to create texture from surface");
        }
        
        SDL_Rect renderQuad = {coordinates.x, coordinates.y, textSurface->w, textSurface->h};
        if(is_centered){
            renderQuad.x -= textSurface->w/2;
        }
        SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
        SDL_DestroyTexture(textTexture); 
        SDL_FreeSurface(textSurface);
        return renderQuad;
    }
    else{
        throw std::runtime_error("zero length text");
    }
}

void GUIDrawText::redirectText(textMessage text){
    switch(text.position){
        case textPosition::title:
            title = text;
            break;
        case textPosition::log:
            for(int i = seabattle::LOG_LENGTH-1; i != 0; i--){
                log[i] = log[i-1];
            }
            log[0] = text;
    }
}

void GUIDrawText::drawTitle(){
    point2d top_indent(0, 10);
    point2d coordinates = point2d(seabattle::WIDTH/2, 0) + top_indent;
    if(title.msg.size() != 0){
        this->drawText(title.msg, coordinates, enumToColor(title.color), big, true);
    }
}

void GUIDrawText::drawLog(){
    point2d indent = {12, 0};
    point2d coordinates = point2d(seabattle::WIDTH/6, seabattle::HEIGHT*11/12) - indent;
    for(int i = 0; i != seabattle::LOG_LENGTH; i++){
        if(log[i].msg.size() != 0){
            SDL_Rect outline = {coordinates.x-3, coordinates.y, seabattle::WIDTH/3, seabattle::SMALL_FONT_SIZE};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
            SDL_RenderFillRect(renderer, &outline);
            SDL_Rect renderQuad = this->drawText(log[i].msg, coordinates, enumToColor(log[i].color), small);
            
            
            coordinates -= point2d(0, renderQuad.h);
        }
    }
}

void GUIDrawText::operator()(){
    this->drawLog();
    this->drawTitle();
}

void GUIDrawText::setRenderer(SDL_Renderer * renderer){
    this->renderer = renderer;
}

GUIDrawText::~GUIDrawText(){
    TTF_CloseFont(big_font);
    TTF_CloseFont(medium_font);
    TTF_CloseFont(small_font);
    TTF_Quit();
}