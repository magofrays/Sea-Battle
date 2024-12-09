#ifndef SEABATTLE_H
#define SEABATTLE_H

#include "states/Game.h"
#include "IO/gameController.h"
#include "IO/gameTracker.h"

template<typename gameInput, typename gameOutput>
class SeaBattle{
    Game game;
    gameTracker<gameOutput> tracker;
    gameController<gameInput> controller;
    public:
        SeaBattle() : tracker(game), controller(game){}

        void run(){
            while(game.running){
                controller.update();
                game.update();
                tracker.update();
            }
        }
};

#endif