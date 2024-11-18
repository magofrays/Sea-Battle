#include "IO/GUIInput.h"
#include "IO/GUIOutput.h"
#include "states/Game.h"

int main(){
    
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