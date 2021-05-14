#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "LinkedList.h"
#include "Tile.h"

class Player {
  Player(std::string name);

  // Custom Functions
  void addPoints(int points);
  void drawTile(Tile *tile);

  // Getters
  LinkedList getHand();
  std::string getPlayerName();
  int getScore();
  LinkedList *getHandLinkedList();

  // toString
  void toStringHand();

private:
  std::string name;
  int score;
  LinkedList hand;
};

#endif