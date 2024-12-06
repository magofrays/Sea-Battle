#include "IO/GUIInput.h"
#include "IO/GUIOutput.h"
#include "states/Game.h"
#include "IO/gameController.h"

int main(){
    gameController<GUIInput, GUIOutput> control;

    return 0;
}