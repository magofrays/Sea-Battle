#include "IO/GUIInput.h"
#include "IO/GUIOutput.h"
#include "states/Game.h"
#include "IO/gameController.h"

int main(){
    Game game;
    gameController<GUIInput, GUIOutput> control(game);

    return 0;
}