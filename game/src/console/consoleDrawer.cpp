#include "consoleDrawer.h"

void consoleDrawer::drawField(playField & play_field, bool fog){
    box2d field_area = play_field.getArea();
    for(int y = field_area.max_point.y-1; y != field_area.min_point.y-1; --y){
        for(int x = 0; x != field_area.max_point.x; x++){
            playField::Cell cell = play_field.getCell(x, y);
            if(fog){
                if(cell.state == playField::Cell::unknown){
                    std::cout << "# ";
                }
                else{
                    if(cell.state == playField::Cell::empty){
                        std::cout << "- ";
                    }
                    else{
                        std::cout << (*(cell.segment)).state << " ";
                    }
                }
            }
            else{
                if(!(cell.segment)){
                    std::cout << "- ";
                }
                else{
                    std::cout << (*(cell.segment)).state << " ";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}