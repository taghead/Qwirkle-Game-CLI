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

class GameEngine {
public:

  GameEngine();
  ~GameEngine();

  void saveGame(std::string filename);
  void loadGame(std::string filename);

  void addPlayer(std::string playerName);
  void createTileBag();
  void drawTiles();
  void qwirkleEngine();
  void printBoard();
  void printWinner();
  void userInput(std::string userInput);
  bool tilePlace(std::string tile, std::string location, int index);
  bool tileReplace(int index);
  bool checkNeighbourTiles(Tile *tile, int row, int col);
  bool checkSingleTile(Tile *tile, int row, int col, int dir);
  bool checkMultipleTile(Tile *tile, int count, int row, int col, int dir);
  bool checkExistingTile(Tile *tile, int row, int col);
  bool checkDuplicateTile(int row, int col);
  void changeTurn();
  int  calcPoints(int row, int col);
  int  countTiles(int row, int col, int dir);
  void setLine(int &r, int &c, int dir);

  Player* currentPlayer;

private:
  LinkedList tileBag;
  int numOfPlayers;
  int numOfTurns;
  int currentTurn = 0;
  int tilesPlaced = 0;
  bool turnCheck = false;
  std::vector<Player*> playersArr;

  std::vector<std::vector<Tile*>> board{26, std::vector<Tile*>(26, nullptr)};
  
};

#endif // ASSIGN2_GAME_ENGINE_H