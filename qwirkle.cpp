
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>


#include "LinkedList.h"
#include "GameEngine.h"

#define EXIT_SUCCESS    0

void printGreeting();
void printMenu();
void printCredits();

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   printGreeting();
   printMenu();

   bool inGame = true;
   GameEngine* game = new GameEngine();
   do {

      char choice;
      std::cin >> choice;

      if (!std::cin.eof()){
         if ( choice == '1' ) {
            game->newGame();
         }
         else if ( choice == '2' ){
              std::cout   << std::endl 
                          << "Enter the filename from which to load a game" 
                          << std::endl << "> ";

                  std::string filename;
                  std::cin >> filename;

              // Load Game TODO Read Section 2.2.2
                std::string x;
                std::ifstream infile;

                infile.open(filename);
                if (!infile) {
                  std::cout << "not file found with that name. Try again." << std::endl;

                }
                while (getline(infile, x)) {
                  std::cout << x << std::endl;
                }
                infile.close();

            // Load Game TODO Read Section 2.2.2
         }
         else if ( choice == '3' ){
            printCredits();
         }
         else if ( choice == '4' ){
            inGame = false;
         }
         else {
            std::cout << "Invalid Input" << std::endl << "> ";
         }
      }

   } while ( inGame && !std::cin.eof());

   std::cout << std::endl << std::endl << "Goodbye" << std::endl;

   return EXIT_SUCCESS;
}


void printGreeting(){
   std::cout   << "Welcome to Qwirkle!" << std::endl
               << "-------------------" 
               << std::endl;
}

void printMenu(){
   std::cout   << "Menu" << std::endl
               << "----" << std::endl
               << "1. New Game" << std::endl 
               << "2. Load Game" << std::endl 
               << "3. Credits (Show student information)" << std::endl
               << "4. Quit" << std::endl
               << std::endl << "> ";
}

void printCredits(){
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
      << "----------------------------------" << std::endl
      << std::endl << "> ";
}
