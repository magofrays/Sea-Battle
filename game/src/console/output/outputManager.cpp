#include "outputManager.h"
outputManager::outputManager(std::ostream & os): os(os){
}
void outputManager::drawMessage(std::string message){
    os << message;
}
void outputManager::drawField(playField & play_field, bool fog){
    box2d field_area = play_field.getArea();
    os << "   ";
    for(int i = field_area.min_point.x; i != field_area.max_point.x; ++i){
        os << "= ";
    }
    os << "\n";
    for(int y = field_area.max_point.y-1; y != field_area.min_point.y-1; --y){
        os << y << "| ";
        for(int x = 0; x != field_area.max_point.x; x++){
            playField::Cell cell = play_field.getCell(x, y);
            if(fog){
                if(cell.state == playField::Cell::unknown){
                    os << "# ";
                }
                else{
                    if(cell.state == playField::Cell::empty){
                        os << "~ ";
                    }
                    else{
                        if ((*(cell.segment)).state == Ship::Segment::damaged){
                            os << "* ";
                            }
                        else{
                            if ((*(cell.segment)).state == Ship::Segment::normal){
                            os << "o ";
                            }
                            else{
                                os << "X ";
                            }
                        }
                    }
                }
            }
            else{
                if(!(cell.segment)){
                    os << "~ ";
                }
                else{
                    if ((*(cell.segment)).state == Ship::Segment::damaged){
                    os << "* ";
                    }
                    else{
                    if ((*(cell.segment)).state == Ship::Segment::normal){
                    os << "o ";
                    }
                    else{
                        os << "X ";
                    }}
                }
            }
        }
        os << "|\n";
    }
    os << "   ";
    for(int i = field_area.min_point.x; i != field_area.max_point.x; ++i){
        os << "= ";
    }
    os << "\n";
    os << "   ";
    for(int i = field_area.min_point.x; i != field_area.max_point.x; ++i){
        os << i << " ";
    }
    os << "\n";
}

void outputManager::update(){
    system("clear");
}