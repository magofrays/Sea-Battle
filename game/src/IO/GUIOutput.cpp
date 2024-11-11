#include "GUIOutput.h"

GUIOutput::GUIOutput(){
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
    font = TTF_OpenFont("../assets/fonts/font.ttf", 20);
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    }
    SDL_SetRenderDrawColor(renderer, 131, 148, 196, 255);
    SDL_RenderClear(renderer);
}

void GUIOutput::drawField(playField & field, fieldPosition position){
    point2d top_indent(0, 30);
    int field_size = (seabattle::WIDTH/2)*(seabattle::PLAY_FIELD_SIZE);
    point2d coordinates;
    switch(position){
        case fieldPosition::center:
            coordinates = point2d(seabattle::WIDTH/2 - field_size/2, 0) + top_indent;
            break;
        case fieldPosition::left:
            coordinates = point2d(seabattle::WIDTH/2 - field_size, 0) + top_indent;
            break;
        case fieldPosition::right:
            coordinates = point2d(seabattle::WIDTH/2, 0) + top_indent;
    }
    SDL_SetRenderDrawColor(renderer, 131, 148, 196, 255);
    SDL_Rect rect = {.x = coordinates.x, .y = coordinates.y, .w=field_size, .h = field_size};
    SDL_RenderFillRect(renderer, &rect);
    box2d size = field.getArea();
    int size_x = size.max_point.x;
    int size_y = size.max_point.y;
    int size_cell = std::min(
        (field_size)/size_x,
        (field_size)/size_y
    );
    SDL_Rect field_outline = {.x = coordinates.x-10, .y = coordinates.y-10, .w = size_x*size_cell+20, .h = size_y*size_cell+20};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &field_outline);
    
    for(int x = 0; x != size_x; x++){
        for(int y = 0; y != size_y; y++){
            SDL_Rect cell = {.x = coordinates.x + x*size_cell, .y = coordinates.y + y*size_cell, .w = size_cell, .h = size_cell};
            SDL_Rect outline = {.x = coordinates.x-1 + x*size_cell, .y = coordinates.y-1 + y*size_cell, .w = size_cell+2, .h = size_cell+2};
            SDL_SetRenderDrawColor(renderer, 96, 133, 233, 255);
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 100);
            SDL_RenderDrawRect(renderer, &cell);
            SDL_RenderDrawRect(renderer, &outline);
        }
    }
}


void GUIOutput::drawText(point2d coordinates, std::string text){
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << "\n";
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << "\n";
        SDL_FreeSurface(textSurface);
        return; 
    }

    SDL_Rect renderQuad = {coordinates.x, coordinates.y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
    SDL_DestroyTexture(textTexture); 
    SDL_FreeSurface(textSurface);
}   

GUIOutput::~GUIOutput(){
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
}

void GUIOutput::update(){
    
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 131, 148, 196, 255);
    SDL_RenderClear(renderer);
}

void GUIOutput::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(textMessage)){
        Message * msg = &(*message);
        textMessage * tr_msg = dynamic_cast<textMessage*>(msg);
        drawText(tr_msg->coordinates, tr_msg->info);
    }
    if(typeid(*message) == typeid(playFieldMessage)){
        Message * msg = &(*message);
        playFieldMessage * tr_msg = dynamic_cast<playFieldMessage*>(msg);
        drawField(tr_msg->info, tr_msg->position);
    }
}


