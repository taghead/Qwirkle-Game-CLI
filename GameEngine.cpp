
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "GameEngine.h"
#include "TileCodes.h"
#include "LinkedList.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::newGame(){
   std::cout << std::endl << "Starting a New Game" << std::endl << std::endl;
   int numOfPlayers = 2;
   LinkedList* playerHands[MAX_PLAYERS];
   std::string players[MAX_PLAYERS];

   for ( int i=0; i < numOfPlayers; i++){
      bool isValidInput = true;
      do {
         std::cout   << "Enter a name for player " << i+1 
            << " (uppercase characters only)" << std::endl << "> ";

         isValidInput = true;
         std::cin >> players[i];
         std::cin.ignore(); // Prevents carriage return
         for ( unsigned int j = 0; j < players[i].length(); j++){
            //Check if lowercase
            if ( (players[i][j] >= *"a" && players[i][j] <= *"z") ||  
                 (players[i][j] >= *"0" && players[i][j] <= *"9") ){
               isValidInput = false;
            }

         }

         if (!isValidInput){
            std::cout << std::endl << "Invalid. MUST USE UPPERCASE" << std::endl;
         }
         else if (isValidInput){
           // Create hand for player
           playerHands[i] = new LinkedList();           
         }
      }  while (!isValidInput);      
   }

  // Populate tilebag
  LinkedList* tileBag = new LinkedList();
  tileBag->populateLinkedList();

  std::cout << std::endl << "Let's Play!" << std::endl;

  startGame(numOfPlayers, players, tileBag, playerHands);
}

void GameEngine::startGame(int numOfPlayers, std::string players[MAX_PLAYERS],
                          LinkedList* tileBag, 
                          LinkedList* playerHands[MAX_PLAYERS]){
   bool inGame = true;
   int playersScores[MAX_PLAYERS];
   int boardDim[] = { 6,6 };

   // Save states
   std::vector<std::string> boardState;

   while(inGame){
      for ( int i=0; i<numOfPlayers; i++){
         if (inGame){
            // Tile Display
            std::cout << players[i] << ", it's your turn" << std::endl;
            for ( int i=0; i<numOfPlayers; i++){
               std::cout   << "Score for " << players[i] << ":" 
                           << playersScores[i] << std::endl;
            }

            // Integers for columns
            for ( int i=0; i<boardDim[0]; i++){
               if ( i == 0 ){
                  std::cout << "  ";
                  for ( int j=0; j<boardDim[1]; j++){
                     std::cout << j << "  ";
                  }
                  std::cout << std::endl << " ";
                  for ( int j=0; j<boardDim[1]; j++){
                     std::cout << "---";
                  }
               }

               // Uppercase Letters for rows
               std::cout << std::endl;
               char letter = *"A";
               char currentLetter = letter+i;
               std::cout << currentLetter;
               
               // Print this rows tiles and spaces
               for ( int j=0; j<boardDim[1]; j++){
                  std::cout << "|";
                  // IF TILE PLACED HERE
                     //PRINT TILE
                  // ELSE
                     std::cout << "  ";
               }
               std::cout << "|";
            }

            // User draw max amount of tiles
            playerHands[i]->drawHand(tileBag);

            std::cout << std::endl << std::endl << "Your hand is" << std::endl;
            playerHands[i]->printHand();
            

            // Do user input
            bool inputIsValid = false;
            while (!inputIsValid)
            {
              std::cout << std::endl << "> ";
              std::string userIn;
              std::getline(std::cin,userIn);


              std::vector<std::string> commandsArr;
              std::stringstream  data(userIn);
              std::string tmpString;
              while(std::getline(data,tmpString,' '))
              {
                  commandsArr.push_back(tmpString);
              }

              //place G5 at C4
              if ( commandsArr.size() > 0 ){
                if (commandsArr[0] == "place"){
                  if ( commandsArr.size() > 1 ){
                    if ( functionCheckTileFormat(commandsArr[1]) ){
                      if ( commandsArr.size() > 2 ){
                        if (commandsArr[2] == "at"){
                          if ( commandsArr.size() > 3 ){
                            if ( placeTileCheck(boardState,boardDim,
                                                commandsArr[3]) ){
                              //Place tile
                            }
                          }
                        }
                      }
                    }                    
                  }
                }
              }

              if (!inputIsValid){
                std::cout << std::endl << "Invalid Input";
              }
            }
         }
      }
   }
}

bool GameEngine::functionCheckTileFormat(std::string tile){
  bool isValid = false;
  if ( tile[0] == RED || tile[0] == ORANGE || tile[0] == YELLOW ||
       tile[0] == GREEN || tile[0] == BLUE || tile[0] == PURPLE){
    isValid=true;
  }

  int shapeInt = (int)tile[1] - '0';
  if ( shapeInt == CIRCLE || shapeInt == STAR_4 || shapeInt == DIAMOND ||
       shapeInt == SQUARE || shapeInt == STAR_6 || shapeInt == CLOVER){
    isValid=true;
  }
  return isValid;
}

bool GameEngine::placeTileCheck(std::vector<std::string> boardState,
                                int boardDim[1], std::string pos){
  int posNumber = (int)pos[1] - '0';
  bool posNumberIsValid = false;

  if ( posNumber <= boardDim[1]){
    posNumberIsValid = true;
  }
  std::cout << pos[0] << std::endl;
  std::cout << &pos[0] << std::endl;

  return posNumberIsValid;
}