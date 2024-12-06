#include "GUIDrawField.h"

GUIDrawField::GUIDrawField(SDL_Renderer * renderer, pointerMessage & pointer) : renderer(renderer), pointer(pointer){
}


void GUIDrawField::operator()(){
    for(auto & field: fields){
        if(field){
            point2d top_indent(0, 60);
            int field_size = std::max(seabattle::WIDTH/2, seabattle::HEIGHT/2)*(seabattle::PLAY_FIELD_SIZE);
            point2d coordinates;
            switch(field->position){
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
            point2d size = field->field.getArea().max_point + point2d(1, 1);
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
                    if(field->fog){
                        if(field->field.getCell(x, y).state == playField::Cell::unknown){
                                color = seabattle::CELL_UNKNOWN;
                        }
                        else if(field->field.getCell(x, y).state == playField::Cell::empty){
                                color = seabattle::CELL_EMPTY;
                        }
                        else if (field->field.getCell(x, y).state ==  playField::Cell::ship){
                            switch(field->field.getCell(x, y).segment->state){
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
                        if(!(field->field.getCell(x, y).segment)){
                            color = seabattle::CELL_EMPTY;
                            if(field->field.getCell(x, y).state == playField::Cell::unknown){
                                color = seabattle::CELL_EMPTY;
                            }
                            else if(field->field.getCell(x, y).state == playField::Cell::empty){
                                color = seabattle::CELL_ATTACKED;
                            }
                        }
                        else{
                            switch(field->field.getCell(x, y).segment->state){
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
            //output->drawText(field_name, name_coordinates, {255, 255, 255}, medium, true);
            if(field->draw_pointer){
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
        }
    }
}

void GUIDrawField::setField(std::unique_ptr<playFieldMessage> field){
    if(!field){
        fields[0] = nullptr;
        fields[1] = nullptr;
        return;
    }
    switch(field->position){
        case fieldPosition::left:
            fields[0] = field;
            return;
        case fieldPosition::center:
            fields[0] = field;
            return;
        case fieldPosition::right:
            fields[1] = field;
            return;
    }
}
