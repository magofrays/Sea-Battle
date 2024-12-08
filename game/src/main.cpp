#include "IO/GUI/GUIInput.h"
#include "IO/GUI/GUIOutput.h"
#include "states/Game.h"
#include "IO/gameController.h"

int main(){
    gameController<GUIInput, GUIOutput> control;
    control.run();
    return 0;
}