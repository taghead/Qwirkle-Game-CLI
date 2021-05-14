#include "GameEngine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#include <sstream>

GameEngine::GameEngine() {
  numOfPlayers = INITIAL_NUM_PLAYERS;
  turnCount = INITIAL_TURN_COUNT;
  // Initialize the board
  for (int y = 0; y < BOARD_DIM; y++) {
    for (int x = 0; x < BOARD_DIM; x++) {
      board[y][x] = nullptr;
    }
  }
}

GameEngine::~GameEngine() {
  // Delete the board
  for (int y = 0; y < BOARD_DIM; y++) {
    for (int x = 0; x < BOARD_DIM; x++) {
      delete board[y][x];
    }
  }
  // Delete players
  for (unsigned int i = 0; i < playersArr.size(); i++) {
    delete playersArr[i];
  }
}

void GameEngine::saveGame(std::string filename) {
  std::ofstream fileStream;
  // Creates file
  fileStream.open(filename);

  for (unsigned int i = 0; i < playersArr.size(); i++ ){
    // Saves Player Name
    fileStream << playersArr[i]->getPlayerName() << std::endl;
    // Saves Player Score
    fileStream << playersArr[i]->getPlayerScore() << std::endl;
    // Saves Player Hand
    fileStream << playersArr[i]->getPlayerHand().toStringHand() << std::endl;
  }
  // Saves Board size
  fileStream << BOARD_DIM << "," << BOARD_DIM << std::endl;

  std::string saveBoard;
  for (unsigned int y = 0; y < board.size(); y++) {
    for (unsigned int x = 0; x < board.size(); x++) {
      if (board[y][x] != nullptr) {
        char alpha[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
        // Saves order of placed tiles and location
        saveBoard += board[y][x]->toString() + "@" + alpha[y] 
                  + std::to_string(x) + ",";
      }
    }
  }
  // Adds saveBoard variables to file
  fileStream << saveBoard << std::endl;
  // Adds remaining tile bag to file
  fileStream << tileBag.toStringHand() << std::endl;
  // Adds current player to file
  fileStream << currentPlayer->getPlayerName() << std::end;
  // Closes file
  fileStream.close();
}