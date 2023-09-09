#include "../GameState/GameState.h"
#include "../TennisConstants/TennisConstants.h"
#include "../Logger/Logger.h"
#include <fstream>
#include <string>
#include "../Player/Player.h"

class SubjectManager {
public:
    SubjectManager();
    ~SubjectManager();
    void gameStateUpdate( GameState* gameState, Player* player1, Player* player2 );
private:
    Logger* _logger;
};
