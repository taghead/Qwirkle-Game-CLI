
#include <iostream>
#include <string>
#include <vector>

#include "GameEngine.h"
#include "TileCodes.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::newGame(){
   std::cout << std::endl << "Starting a New Game" << std::endl << std::endl;

   int numOfPlayers = 2;
   std::string players[MAX_PLAYERS];
   for ( int i=0; i < numOfPlayers; i++){
      bool isValidInput = true;
      do {
         std::cout   << "Enter a name for player " << i+1 
            << " (uppercase characters only)" << std::endl << "> ";

         isValidInput = true;
         std::cin >> players[i];
         for ( unsigned int j = 0; j < players[i].length(); j++){

            if ( players[i][j] >= *"a" && players[i][j] <= *"z" ){
               isValidInput = false;
            }

         }

         if (!isValidInput){
            std::cout << std::endl << "Invalid. MUST USE UPPERCASE" << std::endl;
         }
      }  while (!isValidInput);      
   }

   std::cout << std::endl << "Let's Play!" << std::endl;

  startGame(numOfPlayers, players);
}

void GameEngine::startGame(int numOfPlayers, std::string players[MAX_PLAYERS]){
   bool inGame = true;
   int playersScores[MAX_PLAYERS];
   int boardDim[] = { 6,6 };

   // Save states
   std::vector<std::string> boardState;

   for ( int i=0; i<AMOUNT_OF_COLORS; i++){
      for ( int j=0; j<AMOUNT_OF_SHAPES; j++){
         for ( int j=0; j<AMOUNT_OF_TILES_PER; j++){
            if ( i == 0 ){
               // Create Tile
               // Add Tile to Node
               // Add Tile to LinkedList
            }
         }
      }
   }


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
            std::cout << std::endl << "> ";

            std::string userIn;
            std::cin >> userIn;
         }
      }
   }
}