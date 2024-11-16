#include "GUIOutput.h"
#include <filesystem>

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
        for(int y = size_y-1; y != -1; y--){
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
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 100);
            SDL_RenderDrawRect(renderer, &cell);
            SDL_RenderDrawRect(renderer, &outline);
            point2d field_indent(10, 0);
            point2d name_coordinates = point2d(field_outline.w/2+field_outline.x, field_outline.h+field_outline.y) + field_indent;
            this->drawText(field_name, name_coordinates, medium, {255, 255, 255, 255}, true);
            if(draw_pointer){
                this->drawPointer(size_cell, coordinates, size.max_point);
            }

        }
    }
}

void GUIOutput::drawPointer(int size_cell, point2d coordinates, point2d field_size){
    point2d pointer_coordinates = pointer.coordinates;
    pointer_coordinates.y = std::abs(pointer_coordinates.y - field_size.y);
    SDL_Color color = seabattle::POINTER_COLOR;
    for(int x = pointer.area.min_point.x; x != pointer.area.max_point.x+1; x++){
        for(int y = pointer.area.min_point.y; y != pointer.area.max_point.y+1; y++){
            point2d cell_coordinates = (pointer_coordinates + point2d(x, y)) * size_cell;
            SDL_Rect cell = {.x = coordinates.x + cell_coordinates.x, .y = coordinates.y + cell_coordinates.y, .w = size_cell, .h = size_cell};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 100);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}



SDL_Rect GUIOutput::drawText(std::string text, point2d coordinates, fontSize font_size, 
                        SDL_Color color, bool is_centered){
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



void GUIOutput::update(){
    this->drawTitle();
    this->drawLog();
    SDL_RenderPresent(renderer);
    SDL_Color c = seabattle::BACKGROUND_COLOR;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(renderer);
}

void GUIOutput::redirectText(Text text, textPosition position){
    switch(position){
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
    this->drawText(title.msg, coordinates, big, title.color, true);
}

void GUIOutput::drawLog(){
    point2d bottom_indent(0, -30);
    point2d coordinates = point2d(seabattle::WIDTH/4, seabattle::HEIGHT) + bottom_indent;
    for(int i = 0; i != seabattle::LOG_LENGTH; i++){
        if(log[i].msg.size() != 0){
            SDL_Rect outline = {coordinates.x-3, coordinates.y, seabattle::WIDTH/2, seabattle::SMALL_FONT_SIZE};
            SDL_SetRenderDrawColor(renderer, 70, 70, 70, 100);
            SDL_RenderFillRect(renderer, &outline);
            SDL_Rect renderQuad = this->drawText(log[i].msg, coordinates, small, log[i].color);
            
            
            coordinates -= point2d(0, renderQuad.h);
        }
    }
}

void GUIOutput::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(textMessage)){
        Message * msg = &(*message);
        textMessage * tr_msg = dynamic_cast<textMessage*>(msg);
        redirectText(tr_msg->info, tr_msg->position);
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
