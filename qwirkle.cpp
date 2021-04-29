
#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"

#include <iostream>
#include <string>

#define EXIT_SUCCESS    0

LinkedList newTileBag();

int main(void) {
   bool inGame = true;

   LinkedList tileBag = newTileBag(); //This test call delete for production

   std::cout   << "Welcome to Qwirkle!" << "\n" 
               << "-------------------" 
               << std::endl;
   do {

      std::cout   << "Menu" << std::endl
                  << "----" << std::endl
                  << "1. New Game" << std::endl 
                  << "2. Load Game" << std::endl 
                  << "3. Credits (Show student information)" << std::endl
                  << "4. Quit" << std::endl
                  << std::endl << "> ";

      int choice;
      std::cin >> choice;

      if ( choice == 1 ) {
         std::cout << std::endl << "Starting a New Game" << std::endl;
         // New Game TODO Read Section 2.2.1
      }
      else if ( choice == 2 ){
         std::cout   << std::endl 
                     << "Enter the filename from which load a game" 
                     << std::endl << "> ";

         std::string filename;
         std::cin >> filename;

         // Load Game TODO Read Section 2.2.2
      }
      else if ( choice == 3 ){
         std::cout   << "----------------------------------" << std::endl 
                     << "Name: James Parsell"  << std::endl 
                     << "Student ID: s3599751"  << std::endl
                     << "Email: s3599751@student.rmit.edu.au" << std::endl 
                     << std::endl
                     << "Name: Siang Hii"  << std::endl 
                     << "Student ID: s3668877"  << std::endl
                     << "Email: s3668877@student.rmit.edu.au" << std::endl 
                     << std::endl
                     << "Name: Cameron Tavelli"  << std::endl 
                     << "Student ID: s3668468"  << std::endl
                     << "Email: s3668468@student.rmit.edu.au" << std::endl 
                     << std::endl
                     << "Name: Andrew Chander"  << std::endl 
                     << "Student ID: s3666434"  << std::endl
                     << "Email: s3666434@student.rmit.edu.au" << std::endl 
                     << "----------------------------------" << std::endl;
      }
      else if ( choice == 4 ){
         inGame = false;
         std::cout << "Goodbye" << std::endl;
      }
   } while ( inGame );

   return EXIT_SUCCESS;
}

// Create a new tile bag. Qwirkle contains 108 tiles. Colors*Shapes*3
LinkedList newTileBag(){
   LinkedList* tileBag = new LinkedList();
   std::string colours = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   std::string shapes = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
   for ( int c=0; c<AMOUNT_OF_COLORS; c++ ){
      for ( int s=0; s<AMOUNT_OF_SHAPES; s++ ){ 
         for ( int amount=0; amount<AMOUNT_OF_TILES_PER){
            new Tile(colours[c], shapes[s]);         
         }
         // Add tile to node
         // Add node to LinkedList
      }
   }

   return *tileBag;
}