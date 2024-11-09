#include "../humanPlayer.h"
#include "../gui/guiOutput.h"
#include "gameState.h"
#include "../messages/messageChain.h"
#include "../IO/gameInput.h"
#include "../IO/gameOutput.h"
#include "../states/setupState.h"

class Game: public messageHandler{
    std::shared_ptr<gameState> state;
    messageHandler * handler;
    
    public:
        bool running = true;
        humanPlayer player;
        
        Game(messageHandler * handler);
        Game(std::shared_ptr<gameState> state, messageHandler * handler);
        void Game::setState(gameState & state);
        void execute();
        
        template <typename T>
        void Handle(Message<T> message);
        void setNext(messageHandler * handler);

};