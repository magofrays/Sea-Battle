#include "SeaBattle.h"
#include "IO/GUI/GUIInput.h"
#include "IO/GUI/GUIOutput.h"
#include "IO/TUI/TUIInput.h"

int main(int argc, char *argv[])
{
    SeaBattle<GUIInput, GUIOutput> game;
    game.run();
    return 0;
}