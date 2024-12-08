#include "IO/GUI/GUIInput.h"
#include "IO/GUI/GUIOutput.h"
#include "IO/TUI/TUIInput.h"
#include "states/Game.h"
#include "IO/gameController.h"
#include "IO/gameTracker.h"

int main(int argc, char *argv[]){
    Game game;
    gameTracker<GUIOutput> tracker(game);
    gameController<GUIInput> controller(game);
    while(game.running){
        controller.update();
        game.update();
        tracker.update();
    }
    return 0;
}