
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "TileCodes.h"
#include "LinkedList.h"

class GameEngine {
public:
   GameEngine();
   ~GameEngine();

  void newGame();
private:
  void startGame(int numOfPlayers, std::string players[MAX_PLAYERS],
                 LinkedList* tileBag, LinkedList* playerHands[]);
  bool functionCheckTileFormat(std::string tile);
};

#endif // ASSIGN2_LINKEDLIST_H
