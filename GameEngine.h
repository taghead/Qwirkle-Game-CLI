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

  void saveGame(std::string filename);
  void loadGame(std::string filename);
  void printBoard();
  void userInput();
  void addPlayer(std::string playerName);
  void createTileBag();
  void drawTiles();
  void qwirkleEngine();
  bool tilePlace(std::string tile, std::string location, int index);
  void changeTurn();
  int calculatePoints(int letter, int number);
  bool checkSurroundingTiles(Tile *tile, int letter, int number);
  int countTiles(int letter, int number, int direction);
  bool checkSingleTile(Tile *tile, int letter, int number, int direction);
  bool checkManyTiles(Tile *tile, int tileCount, int letter, int number, int direction);
  bool checkTiles(Tile *tile, int letter, int number, int axis);
  void setLine(int &l, int &n, int direction);
  bool checkDupeTile(Tile *tile, int letter, int number);
  bool checkDupeBeforeTile(int letter, int number);

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