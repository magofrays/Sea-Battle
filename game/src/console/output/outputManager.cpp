#include "outputManager.h"
outputManager::outputManager(std::ostream & os): os(os){
}
void outputManager::drawMessage(std::string message){
    os << message;
}
void outputManager::drawField(playField & play_field, bool fog){
    box2d field_area = play_field.getArea();
    for(int y = field_area.max_point.y-1; y != field_area.min_point.y-1; --y){
        for(int x = 0; x != field_area.max_point.x; x++){
            playField::Cell cell = play_field.getCell(x, y);
            if(fog){
                if(cell.state == playField::Cell::unknown){
                    os << "# ";
                }
                else{
                    if(cell.state == playField::Cell::empty){
                        os << "- ";
                    }
                    else{
                        os << (*(cell.segment)).state << " ";
                    }
                }
            }
            else{
                if(!(cell.segment)){
                    os << "- ";
                }
                else{
                    os << (*(cell.segment)).state << " ";
                }
            }
        }
        os << "\n";
    }
    os << "\n";
}

void outputManager::update(){
    system("clear");
}