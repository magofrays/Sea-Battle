#include "gameState.h"
class playState: public gameState{
    public:
    void execute();
    void Handle(std::unique_ptr<Message> message);
};