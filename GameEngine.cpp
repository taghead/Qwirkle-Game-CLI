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
        char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                        'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                        'W', 'X', 'Y', 'Z'};
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

// LOAD GAME

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
    printBoard();
    currentPlayer->toStringHand();

    if (std::cin.eof())
    {
      std::cout << std::endl
                << "Goodbye!" << std::endl;
      exit(0);
    }
    else
    {
      std::string in;
      std::cout << "> ";
      std::getline(std::cin, in);

      userInput(in);
    }
  }

  // Prints final board
  std::cout << "PRINT FINAL BOARD";
  // printBoard();
  std::cout << "Game Over" << std::endl;

  // Check for winner
}

void GameEngine::printBoard()
{
  // Print numbers
  for (int i = 0; i < BOARD_DIM; i++)
  {
    if (i == 0)
    {
      std::cout << "   " << i;
    }
    else if (i <= 10)
    {
      std::cout << "  " << i;
    }
    else
    {
      std::cout << " " << i;
    }
  }
  std::cout << std::endl;
  // Print hyphens
  for (int i = 0; i < BOARD_DIM + 1; i++)
  {
    // 27*3=81
    std::cout << "---";
  }
  std::cout << std::endl;
  // Print board
  for (int y = 0; y < BOARD_DIM; y++)
  {
    char c = y + 65;
    std::cout << c << " ";
    for (int x = 0; x < BOARD_DIM; x++)
    {
      if (board[y][x] != NULL_TILE)
      {
        std::cout << "|" << board[y][x]->toString();
      }
      else
      {
        std::cout << "|  ";
      }
    }
    std::cout << "|" << std::endl;
  }

  std::cout << std::endl;
}

void GameEngine::userInput(std::string userInput)
{
  bool valid = false;
  int index = 0;

  // Check for "place"
  if (userInput.substr(0, 5) == "place" && userInput.substr(9, 2) == "at")
  {
    std::string selectedTile = userInput.substr(6, 2);

    for (int i = 0; i < currentPlayer->getPlayerHand().getSize(); i++)
    {
      Tile *tileInHand = currentPlayer->getPlayerHand().getTileAt(i);
      if (tileInHand->toString() == selectedTile)
      {
        valid = true;
        index = i;

        i = currentPlayer->getPlayerHand().getSize();
      }
    }
    if (valid)
    {
      std::string location = userInput.substr(12, 14);

      bool tilePlaceCheck = tilePlace(selectedTile, location, index);
      if (tilePlaceCheck)
      {
        tilesPlaced += 1;
        changeTurn();
      }
    }
    else
    {
      std::cout << "Invalid Input" << std::endl;
    }
  }

  // Check for "replace"
  else if (userInput.substr(0, 7) == "replace")
  {
    std::string selectedTile = userInput.substr(8, 2);

    for (int i = 0; i < currentPlayer->getPlayerHand().getSize(); i++)
    {
      Tile *tileInHand = currentPlayer->getPlayerHand().getTileAt(i);
      if (tileInHand->toString() == selectedTile)
      {
        valid = true;
        index = i;

        i = currentPlayer->getPlayerHand().getSize();
      }
    }
    if (valid)
    {
      bool tileReplaceCheck = tileReplace(index);
      if (tileReplaceCheck)
      {
        changeTurn();
      }
    }
    else
    {
      std::cout << "Invalid Input" << std::endl;
    }
  }
  // SAVE

  // LOAD

  // QUIT
}

bool GameEngine::tilePlace(std::string tile, std::string location, int index)
{
  bool isValidPlacement = false;

  // Pointers to players objects
  Tile *selectedTile = currentPlayer->getHandLinkedList()->getTileAt(index);
  LinkedList *playerHand = currentPlayer->getHandLinkedList();

  // Convert coordinate from string to int number
  char ycoord = location.at(0);
  int row = ycoord - 65;

  // Convert coordinate number/s from string to int number
  int col = std::stoi(location.substr(1, 2));

  // Allow player to place tile anywhere on first turn
  if (numOfTurns == INITIAL_TURN_COUNT)
  {
    playerHand->deleteAt(index);
    if (tileBag.getSize() > 0)
    {
      currentPlayer->drawHand(tileBag.getTileAt(0));
      tileBag.deleteFront();
    }
    board[row][col] = selectedTile;
    currentPlayer->addPoints(calcPoints(row, col));
    isValidPlacement = true;
  }
  else
  {
    // Check is space is empty
    if (board[row][col] != NULL_TILE)
    {
      std::cout << "Invalid Input" << std::endl;
      isValidPlacement = false;
    }
    else
    {
      // If surrounding placement is valid
      if (checkNeighbourTiles(selectedTile, row, col))
      {
        playerHand->deleteAt(index);
        if (tileBag.getSize() > 0)
        {
          currentPlayer->drawHand(tileBag.getTileAt(0));
          tileBag.deleteFront();
        }
        // Assigned tile a place on the board
        board[row][col] = selectedTile;
        // Calculate points
        currentPlayer->addPoints(calcPoints(row, col));
        isValidPlacement = true;
      }
      else
      {
        std::cout << "Invalid Input" << std::endl;
        isValidPlacement = false;
      }
    }
  }
  return isValidPlacement;
}

bool GameEngine::tileReplace(int index)
{
  bool tileReplaced = false;
  if (tileBag.getSize() > 0)
  {
    Tile *tileInHand = currentPlayer->getHandLinkedList()->getTileAt(index);
    currentPlayer->getHandLinkedList()->deleteAt(index);
    tileBag.addBack(tileInHand);

    currentPlayer->drawHand(tileBag.getTileAt(0));
    tileBag.deleteFront();
    tileReplaced = true;
  }
  else
  {
    std::cout << "Invalid Input" << std::endl;
  }
  return tileReplaced;
}

bool GameEngine::checkNeighbourTiles(Tile *tile, int row, int col)
{
  // If any tile existed
  bool foundTile;
  // Initialize checks
  bool leftChecked = false, tileIsOnLeftExists = false, tileOnLeftIsValid = false,
       rightChecked = false, tileIsRightExists = false, tileOnRightIsValid = false,
       upChecked = false, tileIsUpExists = false, tileOnUpIsValid = false,
       downChecked = false, tileIsDownExists = false, tileOnDownIsValid = false;

  // Numbers assigned to directions index
  int left = 0, up = 1, right = 2, down = 3;
  int direction[4] = {left, up, right, down};

  // Counter to track number of tiles
  int tileCount = 1;

  // If tile there is a tile to the left
  if (col - 1 >= 0)
  {
    if (board[row][col - 1] != NULL_TILE)
    {
      tileIsOnLeftExists = true;
    }
  }

  // If tile there is a tile to the right
  if (col + 1 <= 25)
  {
    if (board[row][col + 1] != NULL_TILE)
    {
      tileIsRightExists = true;
    }
  }

  // If tile there is a tile above
  if (row - 1 >= 0)
  {
    if (board[row - 1][col] != NULL_TILE)
    {
      tileIsUpExists = true;
    }
  }

  // If tile there is a tile below
  if (row + 1 <= 25)
  {
    if (board[row + 1][col] != NULL_TILE)
    {
      tileIsDownExists = true;
    }
  }

  // If a tile exists in any direction
  if (tileIsOnLeftExists || tileIsRightExists || tileIsUpExists || tileIsDownExists)
  {
    // Parralel arrays to check if tiles have been valid, checked or exists.
    int numberOfDirections = 4;
    bool tilesDirectionExists[4] = {tileIsOnLeftExists, tileIsUpExists,
                                    tileIsRightExists, tileIsDownExists};

    bool tilesChecked[4] = {leftChecked, upChecked,
                            rightChecked, downChecked};

    bool tilesValid[4] = {tileOnLeftIsValid, tileOnUpIsValid,
                          tileOnRightIsValid, tileOnDownIsValid};

    // Uses the parralel arrays to check each direction
    for (int i = 0; i < numberOfDirections; i++)
    {
      if (tilesDirectionExists[i])
      {
        // Counts the amount of tiles of the current direction
        tileCount = countTiles(row, col, direction[i]);
        if (tileCount < 6)
        {

          if (tileCount == 1)
          {
            // If there was only one tile counted
            // tilesChecked[i] = checkSingleTile(tile, row, col, direction[i]);
          }
          else
          {
            // If there was many tiles counted
            // tilesChecked[i] = checkManyTiles(tile, tileCount, row, col, direction[i]);
          }
          // Current direction has been checked
          tilesValid[i] = true;
        }
        else
        {
          std::cout << "Invalid Input" << std::endl;
        }
      }
      else
      {
        tilesChecked[i] = true;
      }
    }

    leftChecked = tilesChecked[0];
    upChecked = tilesChecked[1];
    rightChecked = tilesChecked[2];
    downChecked = tilesChecked[3];

    tileIsOnLeftExists = tilesDirectionExists[0];
    tileIsUpExists = tilesDirectionExists[1];
    tileIsRightExists = tilesDirectionExists[2];
    tileIsDownExists = tilesDirectionExists[3];

    tileOnLeftIsValid = tilesValid[0];
    tileOnUpIsValid = tilesValid[1];
    tileOnRightIsValid = tilesValid[2];
    tileOnDownIsValid = tilesValid[3];
  }

  // Ensure every direction has been checked
  if (leftChecked && upChecked && rightChecked && downChecked)
  {
    if (tileOnLeftIsValid && tileOnRightIsValid)
    {
      // Validate X axis (Column)
      int rowCheck;
      int colCheck;

      setLine(rowCheck, colCheck, direction[0]);
      Tile *tileOne = tile;
      Tile *tileTwo = board[row + rowCheck][col + colCheck];
      Tile *tileThr = board[row - rowCheck][col - colCheck];

      if (tileOne->getColour() == tileTwo->getColour())
      {
        if (tileThr->getColour() == tileOne->getColour())
        {
          foundTile = true;
        }
        else
        {
          foundTile = false;
        }
      }

      else if (tileOne->getShape() == tileTwo->getShape())
      {
        if (tileThr->getShape() == tileOne->getShape())
        {
          foundTile = true;
        }
        else
        {
          foundTile = false;
        }
      }
      else
      {
        foundTile = false;
      }
    }
    else if (tileOnDownIsValid && tileOnUpIsValid)
    {
      // Validate Y axis (Col)
      int rowCheck;
      int colCheck;

      setLine(rowCheck, colCheck, direction[0]);
      Tile *tileOne = tile;
      Tile *tileTwo = board[row + rowCheck][col + colCheck];
      Tile *tileThr = board[row - rowCheck][col - colCheck];

      if (tileOne->getColour() == tileTwo->getColour())
      {
        if (tileThr->getColour() == tileOne->getColour())
        {
          foundTile = true;
        }
        else
        {
          foundTile = false;
        }
      }

      else if (tileOne->getShape() == tileTwo->getShape())
      {
        if (tileThr->getShape() == tileOne->getShape())
        {
          foundTile = true;
        }
        else
        {
          foundTile = false;
        }
      }
      else
      {
        foundTile = false;
      }
    }
    else
    {
      foundTile = true;
    }
  }
  else
  {
    foundTile = false;
  }

  return foundTile;
}

bool GameEngine::checkSingleTile(Tile *tile, int row, int col, int dir)
{
  // Declare
  bool doesColorMatch = false;
  bool doesShapeMatch = false;
  bool isValid = false;

  // Tile
  char tileColour = tile->getColour();
  int tileShape = tile->getShape();

  // Get relative rows and cols
  int checkRow;
  int checkColumn;
  setLine(checkRow, checkColumn, dir);

  // Get relative color
  char boardColour = board[row + checkRow][col + checkColumn]->getColour();
  int boardShape = board[row + checkRow][col + checkColumn]->getShape();

  // Check if tile exists
  if (!checkExistingTile(tile, row + checkRow, col + checkColumn))
  {
    // Check if row is locked into a certain color
    if (tileColour == boardColour)
    {
      doesColorMatch = true;
    }
    // Check if row is locked into a certain shape
    else if (tileShape == boardShape)
    {
      doesShapeMatch = true;
    }
    // Check if it is locked into either color or shape
    if (doesColorMatch || doesShapeMatch)
    {
      isValid = true;
    }
    else
    {
      std::cout << "Invalid Input" << std::endl;
      isValid = false;
    }
  }
  if (checkDuplicateTile(row, col))
  {
    isValid = false;
  }
  return isValid;
}

bool GameEngine::checkMultipleTile(Tile *tile, int count, int row, int col, int dir)
{
  // Declare
  bool dupeDetected = false;
  bool isValid = false;

  // Get relative rows and cols
  int checkRow;
  int checkCol;
  setLine(checkRow, checkCol, dir);

  // Iterate amount of relative tiles counted
  for (int i = 1; i <= count; i++)
  {
    if (checkExistingTile(tile, row + checkRow * i, col + checkCol * i))
    {
      dupeDetected = true;
      i = count;
    }
    else
    {
      dupeDetected = false;
    }
  }
  if (!dupeDetected)
  {
    // Check if locked into color
    Colour colorBoardTileOne = board[row + checkRow][col + checkCol]->getColour();
    Colour colorBoardTileTwo = board[row + (2 * checkRow)][col + (2 * checkCol)]->getColour();

    if (colorBoardTileOne == colorBoardTileTwo)
    {
      if (tile->getColour() == colorBoardTileOne)
      {
        isValid = true;
      }
      else
      {
        std::cout << "Invalid Input" << std::endl;
      }
    }
    else
    {
      //Check if locked into shape
      if (tile->getShape() == board[row + checkRow][col + checkCol]->getShape())
      {
        isValid = true;
      }
      else
      {
        std::cout << "Invalid Input" << std::endl;
      }
    }
  }
  if (checkDuplicateTile(row, col))
  {
    isValid = false;
  }
  return isValid;
}

bool GameEngine::checkExistingTile(Tile *tile, int row, int col)
{
  bool dupe = false;

  if (tile->getColour() == board[row][col]->getColour() &&
      tile->getShape() == board[row][col]->getShape())
  {
    std::cout << "Invalid Input" << std::endl;
    dupe = true;
  }
  return dupe;
}

bool GameEngine::checkDuplicateTile(int row, int col)
{
  bool dupe = true;

  bool rowDupe = false;
  bool colDupe = false;

  int dirCheck[4];

  for (int i = 0; i < 4; i++)
  {
    dirCheck[i] = countTiles(row, col, i);
  }

  if (dirCheck[0] > 0 && dirCheck[2] > 0)
  {
    for (int x = 1; x <= dirCheck[0]; x++)
    {
      for (int y = 1; y <= dirCheck[2]; y++)
      {
        std::string westTile = board[row][col - x]->toString();
        std::string eastTile = board[row][col + y]->toString();

        if (westTile == eastTile)
        {
          rowDupe = true;
          x = dirCheck[0] + 1;
          y = dirCheck[2] + 1;
        }
      }
    }
  }
  if (dirCheck[1] > 0 && dirCheck[3] > 0)
  {
    for (int x = 1; x <= dirCheck[1]; x++)
    {
      for (int y = 1; y <= dirCheck[3]; y++)
      {
        std::string northTile = board[row - x][col]->toString();
        std::string southTile = board[row + y][col]->toString();

        if (northTile == southTile)
        {
          colDupe = true;
          x = dirCheck[1] + 1;
          y = dirCheck[3] + 1;
        }
      }
    }
  }

  if (!rowDupe && !colDupe)
  {
    dupe = false;
  }
  else
  {
    std::cout << "Invalid Input" << std::endl;
  }

  return dupe;
}

void GameEngine::changeTurn()
{
  if (std::cin.eof())
  {
    std::cout << std::endl
              << "Goodbye!" << std::endl;
    exit(0);
  }
  else if ((unsigned)currentTurn == playersArr.size() - 1)
  {
    currentTurn = INITIAL_TURN_COUNT;
    numOfTurns++;
  }
  else
  {
    currentTurn++;
    numOfTurns++;
  }
  currentPlayer = playersArr[currentTurn];
}

int GameEngine::calcPoints(int row, int col)
{
  int score = 0;
  if (numOfTurns == INITIAL_TURN_COUNT)
  {
    score += 2;
  }
  int relativeTile[4];

  for (int i = 0; i < 4; i++)
  {
    relativeTile[i] = countTiles(row, col, i);

    if (relativeTile[i] == 5)
    {
      std::cout << "QWIRKLE!" << std::endl;
      relativeTile[i] = 11;
    }
  }
  for (int i : relativeTile)
  {
    if (i > 0)
    {
      score++;
    }
    score += i;
  }
  return score;
}

int GameEngine::countTiles(int row, int col, int dir)
{
  int numOfTiles = 0;
  int r;
  int c;
  setLine(r, c, dir);
  for (int i = 1; i <= 6; i++)
  {

    int y = row + i * r;
    int x = col + i * c;

    if (y >= 0 && x >= 0)
    {
      if (board[y][x] != NULL_TILE)
      {
        numOfTiles++;
      }
      else
      {
        i = 6;
      }
    }
  }
  return numOfTiles;
}

void GameEngine::setLine(int &r, int &c, int dir)
{
  int left = 0, up = 1, right = 2; // down = 3;

  if (dir == left)
  {
    r = 0;
    c = -1;
  }
  else if (dir == right)
  {
    r = 0;
    c = 1;
  }
  else if (dir == up)
  {
    r = -1;
    c = 0;
  }
  else
  {
    r = 1;
    c = 0;
  }
}