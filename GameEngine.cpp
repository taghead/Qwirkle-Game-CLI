
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "GameEngine.h"
#include "LinkedList.h"
#include "TileCodes.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::newGame() {
  if (!std::cin.eof()) {
    std::cout << std::endl << "Starting a New Game" << std::endl << std::endl;
    int numOfPlayers = 2;
    LinkedList *playerHands[MAX_PLAYERS];
    std::string players[MAX_PLAYERS];

    for (int i = 0; i < numOfPlayers; i++) {
      bool isValidInput = true;
      if (!std::cin.eof()){
          do {
            std::cout << "Enter a name for player " << i + 1
                      << " (uppercase characters only)" << std::endl
                      << "> ";

            isValidInput = true;
            std::cin >> players[i];
            std::cin.ignore(); // Prevents carriage return
            for (unsigned int j = 0; j < players[i].length(); j++) {
              // Check if lowercase
              if ((players[i][j] >= *"a" && players[i][j] <= *"z") ||
                  (players[i][j] >= *"0" && players[i][j] <= *"9")) {
                isValidInput = false;
              }
            }

            if (!isValidInput) {
              std::cout << std::endl << "Invalid. MUST USE UPPERCASE" << std::endl;
            } else if (isValidInput) {
              // Create hand for player
              playerHands[i] = new LinkedList();
            }
          } while (!isValidInput && !std::cin.eof());
        }
      }

    // Populate tilebag
    LinkedList *tileBag = new LinkedList();
    tileBag->populateLinkedList();
    tileBag->shuffleLinkedList();

    // Empty Player Score Array
    int playersScores[MAX_PLAYERS];

    std::cout << std::endl << "Let's Play!" << std::endl;
    startGame(numOfPlayers, players, tileBag, playerHands, 0, playersScores);
  }
}

void GameEngine::startGame(int numOfPlayers, std::string players[MAX_PLAYERS],
                           LinkedList *tileBag,
                           LinkedList *playerHands[MAX_PLAYERS],
                           int currentPlayer,
                           int playersScores[MAX_PLAYERS]) {
  bool inGame = true;
  int boardDim[] = {26, 26};

  // Save states
  std::vector<std::string> boardState;

  while (inGame && !std::cin.eof()) {
      if (inGame) {
        // Tile Display
        std::cout << players[currentPlayer] << ", it's your turn" << std::endl;
        for (int i = 0; i < numOfPlayers; i++) {
          std::cout << "Score for " << players[i] << ":" << playersScores[i]
                    << std::endl;
        }

        // Integers for columns
        for (int i = 0; i < boardDim[0]; i++) {
          if (i == 0) {
            std::cout << "  ";
            for (int j = 0; j < boardDim[1]; j++) {
              if ( j > 9 ){
                std::cout << j << " ";
              }
              else{
                std::cout << j << "  ";
              }
            }
            std::cout << std::endl << " ";
            for (int j = 0; j < boardDim[1]; j++) {
              std::cout << "---";
            }
          }

          // Uppercase Letters for rows
          std::cout << std::endl;
          char letter = *"A";
          char currentLetter = letter + i;
          std::cout << currentLetter;

          // Print this rows tiles and spaces
          for (int j = 0; j < boardDim[1]; j++) {
            std::cout << "|";
            bool tileIsHere = false;
            std::string currentNumber = std::to_string(j);
            for (unsigned int i = 0; i < boardState.size(); i++) {
              if (currentLetter == boardState[i][3]) {
                char tileNumber = boardState[i][4];
                if (currentNumber[0] == tileNumber) {
                  std::cout << boardState[i][0] << boardState[i][1];
                  tileIsHere = true;
                }
              }
            }
            if (!tileIsHere) {
              std::cout << "  ";
            }
          }
          std::cout << "|";
        }

        // User draw max amount of tiles
        playerHands[currentPlayer]->drawHand(tileBag);

        std::cout << std::endl << std::endl << "Your hand is" << std::endl;
        playerHands[currentPlayer]->printHand();

        // Do user input
        bool inputIsValid = false;
        
        while (!inputIsValid && !std::cin.eof()) {
          std::cout << std::endl << "> ";
          std::string userIn;
          std::getline(std::cin, userIn);
         

          std::vector<std::string> inArr; // Input
          std::stringstream data(userIn);
          
          std::string tmpString;
          
          while (std::getline(data, tmpString, ' ')) {
            inArr.push_back(tmpString);
          }

          // place G5 at C4
          if (inArr.size() > 0) {
            if (inArr[0] == "place") {
              if (inArr.size() > 1) {
                if (checkTileFormat(inArr[1])) {
                  if (inArr.size() > 2) {
                    if (inArr[2] == "at") {
                      if (inArr.size() > 3) {
                        if (placeLoactionCheck(boardState, boardDim,
                                               inArr[3])) {
                          if (checkTileInPlayerHand(inArr[1],
                                                    playerHands[currentPlayer])) {
                            boardState.push_back(inArr[1] + "@" +
                                                 inArr[3]);
                           /* Scoring function
                              TODO: 2.3.5 
                              Load board state
                              a = position to inArr[3]
                              Iterate over board state get the tiles relative 
                              to the placed tile and determine the score
                              
                           */
                            inputIsValid = true;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            // IF replace
            if (inArr[0] == "replace") { 
               /*Write code
                  TODO: 2.3.6 Replacing tile in hand
               */
            }
            // IF save game
            if (inArr[0] == "save") { 
               /*Write code
                  TODO: 2.3.7 Save game
               */
            }
          } 
          if (std::cin.eof()){
            inputIsValid = true;
          }
          if (!inputIsValid) {
            std::cout << std::endl << "Invalid Input";
          }
        }
      }
    
    // Change player turn
    if ( currentPlayer == numOfPlayers-1 ){
      currentPlayer = 0;
    }
    else {
      currentPlayer++; 
    }
  }
}

/*
   For the place command
   example...   place P4 at A1

   Ensures the tile (P4) is correctly formatted.
*/
bool GameEngine::checkTileFormat(std::string tile) {
  bool isValid = false;
  if (tile[0] == RED || tile[0] == ORANGE || tile[0] == YELLOW ||
      tile[0] == GREEN || tile[0] == BLUE || tile[0] == PURPLE) {
    isValid = true;
  }

  int shapeInt = (int)tile[1] - '0';
  if (shapeInt == CIRCLE || shapeInt == STAR_4 || shapeInt == DIAMOND ||
      shapeInt == SQUARE || shapeInt == STAR_6 || shapeInt == CLOVER) {
    isValid = true;
  }
  return isValid;
}

/*
   For the place command
   example...   place P4 at A1

   Ensures the coordinates (A1) are correctly formatted.

   And there are no tiles on the location
*/
bool GameEngine::placeLoactionCheck(std::vector<std::string> boardState,
                                    int boardDim[1], std::string pos) {
  int posNumber = (int)pos[1] - '0';
  int posChar = pos[0];
  int posCharRef = *"A";
  bool posIsValid = false;

  if (posNumber < boardDim[1]) {
    if (posChar >= posCharRef && posChar < posCharRef + boardDim[0]) {
      posIsValid = true;
    }
  }

  for (unsigned int i = 0; i < boardState.size(); i++) {
    if (boardState[i][3] == pos[0]) {
      if (boardState[i][4] == pos[1]) {
        posIsValid = false;
      }
    }
  }

   /* TILE PLACEMENT GAME RULES 
   TODO: 2.3.5 Check tile placement

   After the command is given, the program must:
   [./]   1. Check that the command is correctly formatted.
   [.O]   2. Check that the placement of tile is legal according to the rules of Qwirkle.
   */
   
  return posIsValid;
}

/*
   For the place command
   example...   place P4 at A1

   Ensures the tile (P4) exists in players hand
*/
bool GameEngine::checkTileInPlayerHand(std::string tile,
                                       LinkedList *playerhand) {
  bool isInhand = false;
  for (int i = 0; i < playerhand->size(); i++) {
    std::string currentTile =
        playerhand->getTile(i)->getTileColour() +
        std::to_string(playerhand->getTile(i)->getTileShape());
    if (currentTile == tile) {
      playerhand->remove(i);
      isInhand = true;
    }
  }
  return isInhand;
}