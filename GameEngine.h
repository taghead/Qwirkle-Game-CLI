
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "TileCodes.h"

class GameEngine {
public:
   GameEngine();
   ~GameEngine();

  void newGame();
private:
  void startGame(int numOfPlayers, std::string players[MAX_PLAYERS]);
};

#endif // ASSIGN2_LINKEDLIST_H
