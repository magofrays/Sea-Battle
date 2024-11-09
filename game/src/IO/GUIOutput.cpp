#include "GUIOutput.h"

GUIOutput::GUIOutput(){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Sea Battle",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    seabatle::WIDTH, seabatle::HEIGHT,
                                    SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 131, 148, 196, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}

void GUIOutput::drawField(point2d coordinates, playField & field){
    box2d size = play_field.getArea();
    int size_x = size.max_point.x;
    int size_y = size.max_point.y;
    int size_cell = std::min(
        (seabatle::WIDTH/2)/size_x,
        (seabatle::HEIGHT*2/3)/size_y
    );
    for(int x = 0; x != size_x; x++){
        for(int y = 0; y != size_y; y++){
            SDL_Rect cell;
            cell.x = x*size_cell;
            cell.y = y*size_cell;
            cell.w = size_cell;
            cell.h = size_cell;
            SDL_SetRenderDrawColor(renderer, 96, 133, 233, 255);
            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 32, 32, 32, 100);
            SDL_RenderDrawRect(renderer, &cell);
            
        }
    }
    
    SDL_RenderPresent(renderer);
}


GUIOutput::~GUIOutput(){
    if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

template<typename T>
void GUIOutput::Handle(Message<T> message){
    //different messages
}

