#include "gameState.h"

class playState: public gameState{
    point2d & pointer;
    box2d & pointer_area;
    public:
        bool input = false;
        playState(Game * game);
        void execute();
        void end(){}
        void usingAbility();
        void lose();
        void win();
        void Handle(std::unique_ptr<Message> message);
        friend json & operator << (json & data, playState & game_state);
        friend json & operator >> (json & data, playState & game_state);
};