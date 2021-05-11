
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
  void loadGame();
private:
  void startGame(int numOfPlayers, std::string players[MAX_PLAYERS],
                 LinkedList* tileBag, LinkedList* playerHands[],
                 int currentPlayer, int playersScores[MAX_PLAYERS]);
  bool checkTileFormat(std::string tile);
  bool placeLoactionCheck(std::vector<std::string> boardState,
                      int boardDim[1], std::string pos);
  bool checkTileInPlayerHand(std::string tile, LinkedList* playerhand);
};

#endif // ASSIGN2_LINKEDLIST_H
