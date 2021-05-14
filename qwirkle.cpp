#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "LinkedList.h"
#include "TileCodes.h"

#define EXIT_SUCCESS 0

void newGame();
void loadGame();

bool checkUpperCase(std::string name);

// GameEngine *gameEngine;

int main(void) {
  // GameEngine *gameEngine;

  // GREETING
  std::cout << "Welcome to Qwirkle!" << std::endl
  << "-------------------" << std::endl;

  // MENU
  std::cout << "Menu" << std::endl
            << "----" << std::endl
            << "1. New Game" << std::endl
            << "2. Load Game" << std::endl
            << "3. Credits (Show student information)" << std::endl
            << "4. Quit" << std::endl;

  // USER CHOICE
  while (!std::cin.eof()) {
    std::cout << std::endl << "> ";
    
    char choice;
    std::cin >> choice;

    std::cout << std::endl;
    if (choice == '1') {
      newGame();
      // TODO: Create function in other file
    }
    else if (choice == '2') {
      loadGame();
      // TODO: Create function in other file
    }
    else if (choice == '3') {
      std::cout << "----------------------------------" << std::endl
                << "Name: James Parsell" << std::endl
                << "Student ID: s3599751" << std::endl
                << "Email: s3599751@student.rmit.edu.au" << std::endl
                << std::endl
                << "Name: Andrew Chander" << std::endl
                << "Student ID: s3666434" << std::endl
                << "Email: s3666434@student.rmit.edu.au" << std::endl
                << std::endl
                << "Name: Cameron Tavelli" << std::endl
                << "Student ID: s3668468" << std::endl
                << "Email: s3668468@student.rmit.edu.au" << std::endl
                << std::endl
                << "Name: Siang Hii" << std::endl
                << "Student ID: s3668877" << std::endl
                << "Email: s3668877@student.rmit.edu.au" << std::endl
                << "----------------------------------" << std::endl;
    }
    else if (choice == '4') {
      std::cout << "Goodbye!" << std::endl;
      exit(0);
    }
    else if (std::cin.eof()) {
      std::cout << std::endl << "Goodbye!" << std::endl;
      exit(0);
    }
    else {
      std::cout << "Invalid Input" << std::endl;
    }
  }

  return EXIT_SUCCESS;
}

void newGame() {
  std::string playerName;
  int playerCount = 2;
  bool validName = false;

  std::cout << "Starting a New Game"
            << std::endl << std::endl;

  for (int i = 0; i < playerCount; i++) {
    validName = false;
    while (!validName) {
      std::cout << "Enter a name for player " << std::to_string(i + 1)
                << " (uppercase characters only)" << std::endl
                << "> ";
      std::cin >> playerName;

      validName = checkUpperCase(playerName);

      if(!validName && !std::cin.eof()) {
        std::cout << std::endl << "Invalid Input" << std::endl << std::endl;
      }
      else if (std::cin.eof()) {
        std::cout << std::endl << std::endl << "Goodbye!" << std::endl;
        exit(0);
      }
    }
    // ADD PLAYER NAME
  }
  // TILEBAG
  // DRAW 
  // GAMEENGINE
}

void loadGame() {
  bool validFile = false;
  std::string filename;

  while (!validFile && !std::cin.eof())
  {
    std::cout << "Enter the filename to load a game" << std::endl
              << "> ";
    std::cin >> filename;

    if (std::cin.eof()) {
      std::cout << std::endl << std::endl << "Goodbye!" << std::endl;
      exit(0);
    }

    std::ifstream in;
    in.open(filename);

    if (in.fail()) {
      std::cout << "Please enter a correct load filename" << std::endl;
    }
    else {
      validFile = true;
    }
    in.close();
  }

  // LOAD GAME
  // GAMEENGINE
}

bool checkUpperCase(std::string playerName) {
  for (char c : playerName) {
    if (!isupper(c)) {
      return false;
    }
  }
  return true;
}