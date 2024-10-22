#include "consoleDrawer.h"

void consoleDrawer::drawField(playField  & play_field){
    std::pair<int, int> bounds = play_field.getSize();
}
void consoleDrawer::drawPlayerField(playField & play_field){
    std::pair<int, int> bounds = play_field.getSize();
    for(int y = bounds.second-1; y != -1; y--){
        for(int x = 0; x != bounds.first; x++){
            segmentState segment = play_field.getSegmentOrAttack({x, y}, false);
            char ch;
            if (segment == null){
                ch = '*';
            }
            else{
                ch = 'x';
            }
            std::cout << ch << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}