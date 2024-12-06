#include "GUIOutput.h"
#include <filesystem>
#include <iostream>

GUIOutput::GUIOutput() : fieldDrawer(renderer, pointer){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
    }
    window = SDL_CreateWindow("Sea Battle",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    seabattle::WIDTH, seabattle::HEIGHT,
                                    SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 131, 148, 196, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    big_font = TTF_OpenFont(seabattle::FONT_DIR, seabattle::BIG_FONT_SIZE);
    if (big_font == nullptr) {
        std::cerr<< std::filesystem::current_path().string() << TTF_GetError() << "\n";
        throw std::runtime_error("Failed to create font");
    }
    medium_font = TTF_OpenFont(seabattle::FONT_DIR, seabattle::MEDIUM_FONT_SIZE);
    if (medium_font == nullptr) {
        std::cerr<< std::filesystem::current_path().string() << TTF_GetError() << "\n";
        throw std::runtime_error("Failed to create font");
    }
    small_font = TTF_OpenFont(seabattle::FONT_DIR, seabattle::SMALL_FONT_SIZE);
    if (small_font == nullptr) {
        std::cerr<< std::filesystem::current_path().string() << TTF_GetError() << "\n";
        throw std::runtime_error("Failed to create font");
    }
}


SDL_Color GUIOutput::enumToColor(textColor color){
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

SDL_Rect GUIOutput::drawText(std::string text, point2d coordinates, SDL_Color color, fontSize font_size, bool is_centered){
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
            std::cerr << TTF_GetError();
            throw std::runtime_error("Failed to create text surface");
        }
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == nullptr) {
            std::cerr << TTF_GetError();
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




void GUIOutput::redirectText(textMessage text){
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

void GUIOutput::drawTitle(){
    point2d top_indent(0, 10);
    point2d coordinates = point2d(seabattle::WIDTH/2, 0) + top_indent;
    this->drawText(title.msg, coordinates, enumToColor(title.color), big, true);
}

void GUIOutput::drawLog(){
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

void GUIOutput::drawInstructions(){
    point2d indent = {12, 0};
    point2d text_indent = {0, seabattle::SMALL_FONT_SIZE};
    point2d coordinates = point2d(seabattle::WIDTH/2, seabattle::HEIGHT*11/12 - seabattle::SMALL_FONT_SIZE*7) + indent;
    SDL_Rect outline = {coordinates.x-3, coordinates.y, seabattle::WIDTH/3, seabattle::SMALL_FONT_SIZE*8};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 150);
    SDL_RenderFillRect(renderer, &outline);
    this->drawText("========================INSTRUCTIONS========================", coordinates, {0, 0, 0}, small);
    this->drawText("W, A, S, D - to move pointer/change field size", coordinates+text_indent, {0, 0, 0}, small);
    this->drawText("E - to use ability/rotate ship/rotate field", coordinates+text_indent*2, {0, 0, 0}, small);
    this->drawText("Q - to place ships automatically/set field size automatically", coordinates+text_indent*3, {0, 0, 0}, small);
    this->drawText("1 - to save game", coordinates+text_indent*4, {0, 0, 0}, small);
    this->drawText("2 - to load game", coordinates+text_indent*5, {0, 0, 0}, small);
    this->drawText("Also use eng layout to play game", coordinates+text_indent*6, {0, 0, 0}, small);
    this->drawText("===========================================================", coordinates+text_indent*7, {0, 0, 0}, small);
}

void GUIOutput::update(){
    this->drawTitle();
    this->drawLog();
    this->drawInstructions();
    SDL_RenderPresent(renderer);
    SDL_Color c = seabattle::BACKGROUND_COLOR;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(renderer);
}



void GUIOutput::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(textMessage)){
        Message * msg = &(*message);
        textMessage * tr_msg = dynamic_cast<textMessage*>(msg);
        redirectText(*tr_msg);
    }
    if(typeid(*message) == typeid(playFieldMessage)){
        std::unique_ptr<playFieldMessage> derivedPtr(static_cast<playFieldMessage*>(message.release()));
        fieldDrawer.setField(std::move(derivedPtr));
        
    }
    if(typeid(*message) == typeid(pointerMessage)){
        Message * msg = &(*message);
        pointerMessage * tr_msg = dynamic_cast<pointerMessage*>(msg);
        this->pointer = *tr_msg;
    }
}


GUIOutput::~GUIOutput(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(big_font);
    TTF_CloseFont(medium_font);
    TTF_CloseFont(small_font);
    TTF_Quit();
    SDL_Quit();
}
