#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#include <sstream>

#include "GameEngine.h"

GameEngine::GameEngine()
{
  // Sets number of players and turns to initial count
  numOfPlayers = INITIAL_NUM_PLAYERS;
  numOfTurns = INITIAL_TURN_COUNT;
  // Initializes the board with null pointers
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
  // Deletes the board
  for (int y = 0; y < BOARD_DIM; y++)
  {
    for (int x = 0; x < BOARD_DIM; x++)
    {
      delete board[y][x];
    }
  }
  // Deletes players
  for (unsigned int i = 0; i < playersArr.size(); i++)
  {
    delete playersArr[i];
  }
}

void GameEngine::saveGame(std::string filename)
{
  // Declare
  std::string saveBoard;
  std::ofstream outFile;
  // Opens the new file
  outFile.open(filename);
  // Loops through the players and saves name, score and hand
  for (unsigned int i = 0; i < playersArr.size(); i++)
  {
    outFile << playersArr[i]->getPlayerName() << std::endl;
    outFile << playersArr[i]->getPlayerScore() << std::endl;
    outFile << playersArr[i]->getPlayerHand().toStringHand() << std::endl;
  }
  // Saves board dimensions
  outFile << BOARD_DIM << "," << BOARD_DIM << std::endl;
  // Iterates over the board and saves placed tiles to temp variable
  for (unsigned int i = 0; i < board.size(); i++)
  {
    for (unsigned int j = 0; j < board.size(); j++)
    {
      if (board[i][j] != nullptr)
      {
        char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                        'U', 'V', 'W', 'X', 'Y', 'Z'};
        saveBoard +=
            board[i][j]->toString() + "@" + alpha[i] + std::to_string(j) + ",";
      }
    }
  }
  // Saves temp variable, remaining tile bag and current player name
  outFile << saveBoard << std::endl;
  outFile << tileBag.toStringHand() << std::endl;
  outFile << currentPlayer->getPlayerName() << std::endl;
  // Saves and closes the new file
  outFile.close();
}

void GameEngine::loadGame(std::string filename)
{
  // Delcare
  std::ifstream in(filename);
  std::string str;
  std::vector<std::string> fileVector;

  // Read the next line from File until it reaches the end.
  while (std::getline(in, str))
  {
    fileVector.push_back(str);
  }

  for (unsigned int i = 0; i < fileVector.size(); i++)
  {
    // fileVector[i] is the line in the file
    if (i == 0)
    {
      // Load player 1 name
      std::string name = fileVector[i];
      addPlayer(name);
    }
    if (i == 1)
    {
      // Load player 1 score
      int playerScoreScoreInt = std::stoi(fileVector[i]);
      playersArr.at(0)->addPoints(playerScoreScoreInt);
    }
    if (i == 2)
    {
      // Load player 1 hand
      std::istringstream playerOneHandStream(fileVector[i]);
      std::string playerOneTile;
      while (std::getline(playerOneHandStream, playerOneTile, ','))
      {
        char colour = playerOneTile.at(0);
        int shape = stoi(playerOneTile.substr(1));
        playersArr.at(0)->drawHand(new Tile(colour, shape));
      }
    }
    if (i == 3)
    {
      // Load player 2 name
      std::string name = fileVector[i];
      addPlayer(name);
    }
    if (i == 4)
    {
      // Load player 2 score
      int playerScoreScoreInt = std::stoi(fileVector[i]);
      playersArr.at(1)->addPoints(playerScoreScoreInt);
    }
    if (i == 5)
    {
      // Load player 2 hand
      std::istringstream playerTwoHandStream(fileVector[i]);
      std::string playerTwoTile;
      while (std::getline(playerTwoHandStream, playerTwoTile, ','))
      {
        char colour = playerTwoTile.at(0);
        int shape = stoi(playerTwoTile.substr(1));
        playersArr.at(1)->drawHand(new Tile(colour, shape));
      }
    }
    if (i == 6)
    {
      // Load Board Shape
    }
    if (i == 7)
    {
      // Load board State
      std::stringstream data(fileVector[i]);
      std::string tmpString;

      char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                      'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                      'U', 'V', 'W', 'X', 'Y', 'Z'};

      int alphaNum[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

      while (std::getline(data, tmpString, ','))
      {
        // Get color and shape
        char colour = tmpString.at(0);
        int shape = stoi(tmpString.substr(1));

        // Convert row alpha to numeric
        int row = 0;
        for (int i = 0; i < 26; i++)
        {
          if (tmpString.at(3) == alpha[i])
          {
            row = alphaNum[i];
          }
        }

        // Convert col to int
        std::string tmpColString = tmpString;
        tmpColString.erase(0, 4);
        int col;
        std::stringstream ss;
        ss << tmpColString;
        ss >> col;
        ss.clear();

        // Add tile to board
        board[row][col] = new Tile(colour, shape);

        // Add turn counter
        numOfTurns += 1;
      }
    }
    if (i == 8)
    {
      // Load tilebag
      std::istringstream tileBagStream(fileVector[i]);
      std::string tile;
      while (std::getline(tileBagStream, tile, ','))
      {
        char colour = tile.at(0);
        int shape = stoi(tile.substr(1));
        tileBag.addBack(new Tile(colour, shape));
      }
    }
    if (i == 9)
    {
      // Load current player's turn
      for (unsigned int j = 0; j < playersArr.size(); j++)
      {
        if (fileVector[i] == playersArr[j]->getPlayerName())
        {
          currentPlayer = &*playersArr[j];
          currentTurn = j;
        }
      }
    }
  }

  std::cout << std::endl
            << "Qwirkle game successfully loaded" << std::endl;
}

void GameEngine::addPlayer(std::string name)
{
  // Adds a new player and adds to the number of players
  playersArr.push_back(new Player(name));
  numOfPlayers++;
}

void GameEngine::createTileBag()
{
  // Declare
  std::random_device random;
  int randomNum = 0;
  std::map<int, char> colourMap = {{0, RED}, {1, ORANGE}, {2, YELLOW}, 
                                  {3, GREEN}, {4, BLUE}, {5, PURPLE}};
  std::map<int, int> shapeMap = {{0, CIRCLE}, {1, STAR_4}, {2, DIAMOND}, 
                                {3, SQUARE}, {4, STAR_6}, {5, CLOVER}};
  // Iterates over the colour and shape vectors to populate tile bag
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
  // Iterate over the max amount of tiles (a full tile bag)
  for (int i = 0; i < MAX_NO_OF_TILE; i++)
  {
    // Obtain random number
    std::uniform_int_distribution<int> uniform_dist(0, MAX_NO_OF_TILE - 1 - i);
    randomNum = uniform_dist(random);

    // Move random tiles to the back of the tile bag
    tileBag.addBack(new Tile(*(tileBag.getTileAt(randomNum))));
    tileBag.deleteAt(randomNum);
  }
}

void GameEngine::drawTiles()
{
  // Iterates over each player and draws a tile from the tile bag
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
  // Set current player if not already set
  if (currentPlayer == nullptr)
  {
    currentPlayer = &*playersArr[0];
  }
  // Create win condition check
  bool winConditionCheck = false;
  for (Player *p : playersArr)
  {
    // Checks if both the current players hand and the tile bag is empty
    if (p->getHandLinkedList()->getSize() == 0 && tileBag.getSize() == 0)
    {
      p->addPoints(6);
      winConditionCheck = true;
    }
  }
  // Print initial board
  printBoard();
  // Checks for win condition and EOF
  while (!winConditionCheck && !std::cin.eof())
  {
    // Checks EOF
    if (std::cin.eof())
    {
      std::cout << std::endl
                << "Goodbye!" << std::endl;
      exit(0);
    }
    else
    {
      // Asks for user input
      std::string in;
      std::cout << "> ";
      std::getline(std::cin, in);
      // Fixes immediate input
      if (in == "")
      {
        std::getline(std::cin, in);
      }
      // Overloads function with user input
      userInput(in);
    }
  }

  // Prints final board
  std::cout << std::endl;
  printBoard();
  std::cout << "Game Over" << std::endl;

  // Prints winner
  printWinner();
}

void GameEngine::printBoard()
{
  // Displays players turn
  std::cout << std::endl
            << currentPlayer->getPlayerName()
            << ", it's your turn!" << std::endl;
  // Displays all players scores
  for (int i = 0; i < numOfPlayers; i++)
  {
    std::cout << "Score for " << playersArr[i]->getPlayerName() << ": "
              << playersArr[i]->getPlayerScore() << std::endl;
  }

  // Get board dimension
  int boardDimY = 1;
  int boardDimX = 1;
  for (int y = 0; y < BOARD_DIM; y++)
  {
    for (int x = 0; x < BOARD_DIM; x++)
    {
      if (board[y][x] != NULL_TILE)
      {
        // Grab the dimensions and account for last row
        if ( x == BOARD_DIM || x == BOARD_DIM-1 ){
          boardDimX = x+1;
        }
        else if ( x < BOARD_DIM ) {
          boardDimX = x+2;
        }
        if ( y == BOARD_DIM || y == BOARD_DIM-1 ){
          boardDimY = y+1;
        }
        else if ( y < BOARD_DIM ){
          boardDimY = y+2;
        }
      }
    }
  }

  // Prints numbers
  for (int i = 0; i < boardDimX; i++)
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
  // Prints hyphens (27*3=81)
  for (int i = 0; i < boardDimX + 1; i++)
  {
    std::cout << "---";
  }
  std::cout << std::endl;
  // Prints board
  for (int y = 0; y < boardDimY; y++)
  {
    // converts int to char
    char c = y + 65;
    std::cout << c << " ";
    for (int x = 0; x < boardDimX; x++)
    {
      if (board[y][x] != NULL_TILE)
      {
        // Prints board tile
        std::cout << "|" << board[y][x]->toString();
      }
      else
      {
        // Prints empty space
        std::cout << "|  ";
      }
    }
    std::cout << "|" << std::endl;
  }
  std::cout << std::endl;
  // Prints the current players hand
  currentPlayer->toStringHand();
}

void GameEngine::printWinner()
{
  // Declare
  bool draw = false;
  int winningScore = 0;
  std::string winner;
  // Iterates through players
  for (Player *player : playersArr)
  {
    // Gets the players final score
    int finalScore = player->getPlayerScore();
    // Checks if player score is greater than the winning score
    if (finalScore > winningScore)
    {
      // Adds winning score and current player name
      winningScore = finalScore;
      winner = player->getPlayerName();
    }
    // checks if both scores are equal
    else if (finalScore == winningScore)
    {
      draw = true;
      // Adds all player names that drew
      winner += player->getPlayerName() + ' ';
    }
    // Displays player score
    std::cout << "Score for " << player->getPlayerName()
              << ": " << player->getPlayerScore() << std::endl;
  }
  // Checks for draw and prints winner/s
  if (!draw)
  {
    std::cout << "Player " << winner << " won!" << std::endl;
  }
  else
  {
    std::cout << "Players " << winner << "drew!" << std::endl;
  }
}

void GameEngine::userInput(std::string userInput)
{
  // Stores if valid input
  bool valid = false;
  // Stores index of tile in player hand
  int index = 0;
  // Checks for "place"
  if (userInput.substr(0, 5) == "place" && userInput.substr(9, 2) == "at")
  {
    std::string selectedTile = userInput.substr(6, 2);
    // Obtains index of selected tile
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
      // Obtains location (example A25)
      std::string location = userInput.substr(12, 3);
      // Ensure lettering is in a legal range and an number exists
      if ((location[0] >= *"A" && location[0] <= *"Z" &&
           location[1]) ||
          (location[0] >= *"A" &&
           location[0] <= *"Z" && location[1] && location[2]))
      {
        bool typo = false;
        // Iterate over the last 2 characters of the location (example 25)
        for (unsigned int i = 1; i < location.size(); i++)
        {
          // Ensure columns are numbers
          if (location[i] >= *"0" && location[i] <= *"9")
          {
            // Convert string to integer
            int tmpLocation;
            std::stringstream ss;
            ss << location.substr(1, 2);
            ss >> tmpLocation;
            ss.clear();
            // Check if columns in the boards range
            if (tmpLocation >= 0 && tmpLocation <= 25)
            {
              valid = true;
            }
            else
            {
              std::cout << "Invalid Input" << std::endl;
              valid = false;
            }
          }
          else
          {
            // If input badly typed
            typo = true;
            valid = false;
          }
        }
        if (typo)
        {
          // If input badly typed
          std::cout << "Invalid Input" << std::endl;
          valid = false;
        }
      }
      else
      {
        std::cout << "Invalid Input" << std::endl;
        valid = false;
      }
      if (valid)
      {
        // After passing all check place the tile
        bool tilePlaceCheck = tilePlace(selectedTile, location, index);
        if (tilePlaceCheck)
        {
          // Increment counter and change turns
          tilesPlaced += 1;
          changeTurn();
        }
      }
    }
    else
    {
      std::cout << "Invalid Input" << std::endl;
    }
    if (valid)
    {
      printBoard();
    }
  }
  // Checks for "replace"
  else if (userInput.substr(0, 7) == "replace")
  {
    // Gets characters for selected tile
    std::string selectedTile = userInput.substr(8, 2);
    // Iterates over the player hand
    for (int i = 0; i < currentPlayer->getPlayerHand().getSize(); i++)
    {
      Tile *tileInHand = currentPlayer->getPlayerHand().getTileAt(i);
      // If the selected tile matches on in hand
      if (tileInHand->toString() == selectedTile)
      {
        valid = true;
        index = i;
        i = currentPlayer->getPlayerHand().getSize();
      }
    }
    // If the selected tile was valid
    if (valid)
    {
      bool tileReplaceCheck = tileReplace(index);
      if (tileReplaceCheck)
      {
        changeTurn();
        printBoard();
      }
    }
    else
    {
      std::cout << "Invalid Input" << std::endl;
    }
  }
  // Checks for "save"
  else if (userInput.substr(0, 4) == "save")
  {
    std::string filename = userInput.substr(5);
    // Overloads the user input to saveGame function
    saveGame(filename);
    std::cout << std::endl
              << "Game successfully saved" << std::endl;
  }
  // Checks for "quit"
  else if (userInput.substr(0, 4) == "quit")
  {
    std::cout << std::endl
              << "Game Over" << std::endl;
    printWinner();
    std::cout << std::endl
              << "Goodbye!" << std::endl;
    exit(0);
  }
  // Checks for EOF
  else if (std::cin.eof())
  {
    std::cout << std::endl
              << std::endl
              << "Goodbye!" << std::endl;
    exit(0);
  }
  // Checks for mismatching sub string
  else if (!std::cin.eof())
  {
    std::cout << "Invalid Input" << std::endl;
    valid = false;
  }
  else
  {
    std::cout << "Invalid Input" << std::endl;
    valid = false;
  }
}

bool GameEngine::tilePlace(std::string tile, std::string location, int index)
{
  // Declare
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
        isValidPlacement = false;
      }
    }
  }
  return isValidPlacement;
}

bool GameEngine::tileReplace(int index)
{
  // Declare
  bool tileReplaced = false;
  // Ensure the tilebag is not empty
  if (tileBag.getSize() > 0)
  {
    // Remove tile from players hand LinkedList
    Tile *tileInHand = currentPlayer->getHandLinkedList()->getTileAt(index);
    currentPlayer->getHandLinkedList()->deleteAt(index);
    tileBag.addBack(tileInHand);
    // Migrate tile from tilebag to players hand
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
  bool leftChecked = false, tileIsOnLeftExists = false,
       tileOnLeftIsValid = false, rightChecked = false,
       tileIsRightExists = false, tileOnRightIsValid = false,
       upChecked = false, tileIsUpExists = false,
       tileOnUpIsValid = false, downChecked = false,
       tileIsDownExists = false, tileOnDownIsValid = false;
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
  if (tileIsOnLeftExists || tileIsRightExists ||
      tileIsUpExists || tileIsDownExists)
  {
    // Parrallel arrays to check if tiles have been valid, checked or exists.
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
            tilesChecked[i] =
                checkSingleTile(tile, row, col, direction[i]);
          }
          else
          {
            // If there was many tiles counted
            tilesChecked[i] =
                checkMultipleTile(tile, tileCount, row, col, direction[i]);
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
    // Reassign variables from arrays to their parent variables
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
      // Declare
      int rowCheck;
      int colCheck;
      setLine(rowCheck, colCheck, direction[0]);
      Tile *tileOne = tile;
      Tile *tileTwo = board[row + rowCheck][col + colCheck];
      Tile *tileThr = board[row - rowCheck][col - colCheck];
      // Validate X axis (Column)
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
      // Declare
      int rowCheck;
      int colCheck;
      setLine(rowCheck, colCheck, direction[0]);
      Tile *tileOne = tile;
      Tile *tileTwo = board[row + rowCheck][col + colCheck];
      Tile *tileThr = board[row - rowCheck][col - colCheck];
      // Validate Y axis (Col)
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

bool GameEngine::checkMultipleTile(Tile *tile, int count, int row,
                                   int col, int dir)
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
    Colour colorBoardTileOne =
        board[row + checkRow][col + checkCol]->getColour();
    Colour colorBoardTileTwo =
        board[row + (2 * checkRow)][col + (2 * checkCol)]->getColour();
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
      if (tile->getShape() ==
          board[row + checkRow][col + checkCol]->getShape())
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
  // Define
  bool dupe = false;
  // Check if tile exists
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
  // Define
  bool dupe = true;
  bool rowDupe = false;
  bool colDupe = false;
  // Check amount of tiles in each direction
  int dirCheck[4];
  for (int i = 0; i < 4; i++)
  {
    dirCheck[i] = countTiles(row, col, i);
  }
  // Check if any dupes exist on the horizontal axis
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
  // Check if any dupes exist on the vertical axis
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
  // If duplicate was found
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
  // Checks for EOF
  if (std::cin.eof())
  {
    std::cout << std::endl
              << "Goodbye!" << std::endl;
    exit(0);
  }
  else if ((unsigned)currentTurn == playersArr.size() - 1)
  {
    // Sets current turn to initial value and adds one to number of turns
    currentTurn = INITIAL_TURN_COUNT;
    numOfTurns++;
  }
  else
  {
    // Adds one to current turn and number of turns
    currentTurn++;
    numOfTurns++;
  }
  // Sets current player
  currentPlayer = playersArr[currentTurn];
}

int GameEngine::calcPoints(int row, int col)
{
  // Declare
  int score = 0;
  // Checks for initial turn
  if (numOfTurns == INITIAL_TURN_COUNT)
  {
    // Always adds 2 points to first player
    score += 2;
  }
  int relativeTile[4];
  // Checks for qwirkle
  for (int i = 0; i < 4; i++)
  {
    relativeTile[i] = countTiles(row, col, i);
    if (relativeTile[i] == 5)
    {
      // Displays player achieving qwirkle and adds score
      std::cout << "QWIRKLE!!" << std::endl;
      relativeTile[i] = 11;
    }
  }
  // For each relative tile, it adds one point to the player score
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
  // Define
  int numOfTiles = 0;
  int r;
  int c;
  // Overloads setLine
  setLine(r, c, dir);
  // Count number tiles in the obtained direction
  for (int i = 1; i <= 6; i++)
  {
    int y = row + i * r;
    int x = col + i * c;
    if (y >= 0 && x >= 0)
    {
      // Check
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
  // Define directions
  int left = 0, up = 1, right = 2; // down = 3;
  // Determine and set pointers to the next row or column based on direction.
  if (dir == left)
  {
    // Set left
    r = 0;
    c = -1;
  }
  else if (dir == right)
  {
    // Set right
    r = 0;
    c = 1;
  }
  else if (dir == up)
  {
    // Set up
    r = -1;
    c = 0;
  }
  else
  {
    // Set down
    r = 1;
    c = 0;
  }
}

  void GameEngine::enableExpandableBoard(){
    expandableBoard = true;
  }

  void GameEngine::disableExpandableBoard(){
    expandableBoard = false;
  }