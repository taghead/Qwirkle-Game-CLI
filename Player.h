#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "LinkedList.h"
#include "Tile.h"

class Player
{
public:
  Player(std::string name);

  // Custom Functions
  void addPoints(int points);
  void drawHand(Tile *tile);

  // Getters
  LinkedList getPlayerHand();
  std::string getPlayerName();
  int getPlayerScore();
  LinkedList *getHandLinkedList();

  // To String
  void toStringHand();

private:
  std::string name;
  int score;
  LinkedList hand;
};

#endif