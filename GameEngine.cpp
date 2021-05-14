#include "GameEngine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#include <sstream>

GameEngine::GameEngine()
{
  numOfPlayers = INITIAL_NUM_PLAYERS;
  numOfTurns = INITIAL_TURN_COUNT;
  // Initialize the board
  for (int y = 0; y < BOARD_DIM; y++)
  {
    for (int x = 0; x < BOARD_DIM; x++)
    {
      board[y][x] = nullptr;
    }
  }
}

GameEngine::~GameEngine()
{
  // Delete the board
  for (int y = 0; y < BOARD_DIM; y++)
  {
    for (int x = 0; x < BOARD_DIM; x++)
    {
      delete board[y][x];
    }
  }
  // Delete players
  for (unsigned int i = 0; i < playersArr.size(); i++)
  {
    delete playersArr[i];
  }
}

void GameEngine::saveGame(std::string filename)
{
  std::ofstream outFile;
  outFile.open(filename);
  for (unsigned int i = 0; i < playersArr.size(); i++)
  {
    outFile << playersArr[i]->getPlayerName() << std::endl;
    outFile << playersArr[i]->getPlayerScore() << std::endl;
    outFile << playersArr[i]->getPlayerHand().toStringHand() << std::endl;
  }

  outFile << BOARD_DIM << "," << BOARD_DIM << std::endl;

  std::string saveBoard;
  for (unsigned int i = 0; i < board.size(); i++)
  {
    for (unsigned int j = 0; j < board.size(); j++)
    {
      if (board[i][j] != nullptr)
      {
        char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        saveBoard += board[i][j]->toString() + "@" + alpha[i] + std::to_string(j) + ",";
      }
    }
  }

  //saveBoard = saveBoard.substr(0, saveBoard.size()-1);

  outFile << saveBoard << std::endl;
  ;

  outFile << tileBag.toStringHand() << std::endl;

  outFile << currentPlayer->getPlayerName() << std::endl;

  outFile.close();
}

void GameEngine::addPlayer(std::string name)
{
  playersArr.push_back(new Player(name));
  std::cout << std::endl;

  numOfPlayers++;
}

void GameEngine::createTileBag()
{
  std::random_device random;
  std::map<int, char> colourMap = {{0, RED}, {1, ORANGE}, {2, YELLOW}, {3, GREEN}, {4, BLUE}, {5, PURPLE}};
  std::map<int, int> shapeMap = {{0, CIRCLE}, {1, STAR_4}, {2, DIAMOND}, {3, SQUARE}, {4, STAR_6}, {5, CLOVER}};
  for (unsigned int i = 0; i < colourMap.size(); i++)
  {
    for (unsigned int j = 0; j < shapeMap.size(); j++)
    {
      for (unsigned int k = 0; k < NO_OF_EACH_TILE; k++)
      {
        tileBag.addBack(new Tile(colourMap[i], shapeMap[j]));
      }
    }
  }
  int randomNum = 0;
  for (int i = 0; i < MAX_NO_OF_TILE; i++)
  {
    std::uniform_int_distribution<int> uniform_dist(0, MAX_NO_OF_TILE - 1 - i);
    randomNum = uniform_dist(random);
    tileBag.addBack(new Tile(*(tileBag.getTileAt(randomNum))));
    tileBag.deleteAt(randomNum);
  }
}

void GameEngine::drawTiles()
{
  for (Player *player : playersArr)
  {
    for (int i = 0; i < MAX_HAND_SIZE; i++)
    {
      Tile *tile = tileBag.getTileAt(0);
      tileBag.deleteFront();
      player->drawHand(tile);
    }
  }
}

void GameEngine::qwirkleEngine()
{
  // Get current player
  currentPlayer = &*playersArr[0];
  // Create win condition check
  bool winConditionCheck = false;
  for (Player *p : playersArr)
  {
    // Checks if both the current players hand and the tile bag is empty
    if (p->getHandLinkedList()->getSize() == 0 && tileBag.getSize() == 0)
    {
      winConditionCheck = true;
    }
  }

  while (!winConditionCheck && !std::cin.eof())
  {
    std::cout << currentPlayer->getPlayerName()
              << ", it's your turn!" << std::endl;
    for (int i = 0; i < numOfPlayers; i++)
    {
      std::cout << "Score for " << playersArr[i]->getPlayerName() << ": "
                << playersArr[i]->getPlayerScore() << std::endl;
    }
    std::cout << "PRINT BOARD" << std::endl;
    //printBoard();
    currentPlayer->toStringHand();

    if (std::cin.eof())
    {
      std::cout << std::endl
                << "Goodbye!" << std::endl;
      exit(0);
    }
    else
    {
      userInput();
    }
  }

  // Prints final board
  std::cout << "PRINT BOARD" << std::endl;
  //printBoard();
  std::cout << "Game Over" << std::endl;

  // Check for winner
}

void GameEngine::userInput()
{
  // Do user input
  bool inputIsValid = false;

  while (!inputIsValid && !std::cin.eof())
  {
    std::cout << std::endl
              << "> ";
    std::string userIn;
    std::getline(std::cin, userIn);

    std::vector<std::string> inArr; // Input
    std::stringstream data(userIn);

    std::string tmpString;

    while (std::getline(data, tmpString, ' '))
    {
      inArr.push_back(tmpString);
    }

    bool skipInvalidOutput = false;
    // place G5 at C4
    if (inArr.size() > 0)
    {
      if (inArr[0] == "place")
      {
        if (inArr.size() > 1)
        {
          {
            if (inArr.size() > 2)
            {
              if (inArr[2] == "at")
              {
                if (inArr.size() > 3)
                {

                  // Do stuff for place tile at here
                  inputIsValid = true;
                }
              }
            }
          }
        }
        // IF replace
        if (inArr[0] == "replace")
        {
          if (inArr.size() > 1)
          {
            // Do replace tile stuff
            inputIsValid = true;
          }
        }
        // IF save game
        if (inArr[0] == "save")
        {
          if (inArr.size() > 1)
          {
            // Do Save Game Stuff
            skipInvalidOutput = true;
          }
        }
        if (inArr[0] == "quit")
        {
          // Do quit game stuff
          inputIsValid = true;
        }
      }
      if (std::cin.eof())
      {
        inputIsValid = true;
      }
      if (!inputIsValid && !skipInvalidOutput)
      {
        std::cout << std::endl
                  << "Invalid Input";
      }
    }
  }
}