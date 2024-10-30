#include "Player.h"
#include "console/input/inputManager.h"
#include "console/output/outputManager.h"

class Game{
    inputManager im;
    outputManager om;
    Player player;
    public:
        Game():im(std::cin), om(std::cout), player(im, om){}
        void Setup();
        void Play();
};