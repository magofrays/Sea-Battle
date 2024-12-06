#include "GUIOutput.h"
#include <filesystem>
#include <iostream>

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

void GUIOutput::drawField(std::string field_name, playField & field, fieldPosition position, bool fog, bool draw_pointer){
    point2d top_indent(0, 60);
    int field_size = std::max(seabattle::WIDTH/2, seabattle::HEIGHT/2)*(seabattle::PLAY_FIELD_SIZE);
    point2d coordinates;
    switch(position){
        case fieldPosition::center:
            coordinates = point2d(seabattle::WIDTH/2 - field_size/2, 0) + top_indent;
            break;
        case fieldPosition::left:
            coordinates = point2d(seabattle::WIDTH/2 - field_size-10, 0) + top_indent;
            break;
        case fieldPosition::right:
            coordinates = point2d(seabattle::WIDTH/2+10, 0) + top_indent;
    }
    SDL_Color color = seabattle::BACKGROUND_COLOR;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {.x = coordinates.x, .y = coordinates.y, .w=field_size, .h = field_size};
    SDL_RenderFillRect(renderer, &rect);
    point2d size = field.getArea().max_point + point2d(1, 1);
    int size_cell = std::min(
        (field_size)/size.x,
        (field_size)/size.y
    );
    SDL_Rect field_outline = {.x = coordinates.x-10, .y = coordinates.y-10, .w = size.x*size_cell+20, .h = size.y*size_cell+20};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &field_outline);
    
    for(int x = 0; x != size.x; x++){
        for(int y = 0; y != size.y; y++){
            SDL_Rect cell = {.x = coordinates.x + x*size_cell, .y = coordinates.y + y*size_cell, .w = size_cell, .h = size_cell};
            SDL_Rect outline = {.x = coordinates.x-1 + x*size_cell, .y = coordinates.y-1 + y*size_cell, .w = size_cell+2, .h = size_cell+2};
            SDL_Color color;
            if(fog){
                if(field.getCell(x, y).state == playField::Cell::unknown){
                        color = seabattle::CELL_UNKNOWN;
                }
                else if(field.getCell(x, y).state == playField::Cell::empty){
                        color = seabattle::CELL_EMPTY;
                }
                else if (field.getCell(x, y).state ==  playField::Cell::ship){
                    switch(field.getCell(x, y).segment->state){
                        case Ship::Segment::normal:
                            color = seabattle::SHIP_SEGMENT_NORMAL;
                            break;
                        case Ship::Segment::damaged:
                            color = seabattle::SHIP_SEGMENT_DAMAGED;
                            break;
                        case Ship::Segment::destroyed:
                            color = seabattle::SHIP_SEGMENT_DESTROYED;
                            break;
                        }
                }    
            }
            else{
                if(!(field.getCell(x, y).segment)){
                    color = seabattle::CELL_EMPTY;
                    if(field.getCell(x, y).state == playField::Cell::unknown){
                        color = seabattle::CELL_EMPTY;
                    }
                    else if(field.getCell(x, y).state == playField::Cell::empty){
                        color = seabattle::CELL_ATTACKED;
                    }
                }
                else{
                    switch(field.getCell(x, y).segment->state){
                        case Ship::Segment::normal:
                            color = seabattle::SHIP_SEGMENT_NORMAL;
                            break;
                        case Ship::Segment::damaged:
                            color = seabattle::SHIP_SEGMENT_DAMAGED;
                            break;
                        case Ship::Segment::destroyed:
                            color = seabattle::SHIP_SEGMENT_DESTROYED;
                            break;
                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
            SDL_RenderDrawRect(renderer, &cell);
            SDL_RenderDrawRect(renderer, &outline);
            
        }
    }
    point2d field_indent(10, 0);
    point2d name_coordinates = point2d(field_outline.w/2+field_outline.x, field_outline.h+field_outline.y) + field_indent;
    this->drawText(field_name, name_coordinates, {255, 255, 255}, medium, true);
    if(draw_pointer){
                this->drawPointer(size_cell, coordinates);
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

void GUIOutput::drawPointer(int size_cell, point2d coordinates){
    SDL_Color color = seabattle::POINTER_COLOR;
    for(int x = pointer.area.min_point.x; x != pointer.area.max_point.x+1; x++){
        for(int y = pointer.area.min_point.y; y != pointer.area.max_point.y+1; y++){
            point2d cell_coordinates = (pointer.coordinates + point2d(x, y)) * size_cell;
            SDL_Rect cell = {.x = coordinates.x + cell_coordinates.x, .y = coordinates.y + cell_coordinates.y, .w = size_cell, .h = size_cell};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
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
        Message * msg = &(*message);
        playFieldMessage * tr_msg = dynamic_cast<playFieldMessage*>(msg);
        drawField(tr_msg->field_name, tr_msg->info, tr_msg->position, tr_msg->fog, tr_msg->draw_pointer);
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
