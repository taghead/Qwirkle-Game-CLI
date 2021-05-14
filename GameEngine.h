#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include <string>
#include <vector>

#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "TileCodes.h"

#define INITIAL_NUM_PLAYERS 0
#define INITIAL_TURN_COUNT  0
#define NULL_TILE           0

#define BOARD_DIM           26
#define NO_OF_EACH_TILE     2
#define MAX_NO_OF_TILE      72
#define MAX_HAND_SIZE       6

#define LEFT                0
#define UP                  1
#define RIGHT               2
#define DOWN                3

class GameEngine {
public:

  GameEngine();
  ~GameEngine();

  // Game Functions
  void saveGame(std::string filename);
  void loadGame(std::string filename);

  void addPlayer(std::string playerName);

  void createTileBag();

  void drawTiles();

  Player* currentPlayer;

private:
  LinkedList tileBag;
  int numOfPlayers;
  int turnCount;
  std::vector<Player*> playersArr;

  std::vector<std::vector<Tile*>> board{26, std::vector<Tile*>(26, nullptr)};
  
};

#endif // ASSIGN2_GAME_ENGINE_H