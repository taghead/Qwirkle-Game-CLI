
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
         for ( unsigned int j = 0; j < players[i].length(); j++){
            //Check if lowercase
            if ( players[i][j] >= *"a" && players[i][j] <= *"z" ){
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
            std::cout << std::endl << "> ";

            // Do user input
            bool inputIsValid = false;
            while (!inputIsValid)
            {
              std::string userIn;
              std::getline(std::cin,userIn);

              std::vector<std::string> result; 
              std::istringstream iss(userIn); 
              for(std::string userIn; iss >> userIn; ) {
                result.push_back(userIn); 
              }

              if (!inputIsValid){
                std::cout << std::endl << "Invalid Input" << std::endl << " >";
              }
            }
         }
      }
   }
}