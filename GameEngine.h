
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <vector>

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
  bool placeTileCheck(std::vector<std::string> boardState,
                      int boardDim[1], std::string pos);
};

#endif // ASSIGN2_LINKEDLIST_H
