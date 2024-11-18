#include "IO/GUIInput.h"
#include "IO/GUIOutput.h"
#include "states/Game.h"
#include "test_handler.h"

int main(){
    
    /*SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("My Window", 
                                      SDL_WINDOWPOS_CENTERED, 
                                      SDL_WINDOWPOS_CENTERED, 
                                      800, 600, 
                                      SDL_WINDOW_SHOWN);
    test_handler handler;
    GUIInput input;
    input.setNext(&handler);
    while(handler.running){
        input.update();
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;*/
    
    GUIInput input;
    GUIOutput output;
    Game game(&output);
    input.setNext(&game);

    while(game.running){
        game.execute();
        input.update();
        output.update();
    }
    return 0;
}