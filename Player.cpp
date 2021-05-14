#include "GameEngine.h"
#include "Player.h"
#include <iostream>
#include <string>

Player::Player(std::string name) {
  this->name = name;
  this->score = 0;
}

void Player::addPoints(int points) {
  this->score += points;
}

void Player::drawTile(Tile *tile) {
  hand.addBack(tile);
}

LinkedList Player::getPlayerHand() {
  return hand;
}

std::string Player::getPlayerName() {
  return name;
}

int Player::getPlayerScore() {
  return score;
}

LinkedList *Player::getHandLinkedList() {
  LinkedList *handPtr = new LinkedList();
  handPtr = &hand;
  return handPtr;
}

void Player::toStringHand() {
  std::cout << "Your hand is" << std::endl;
  // Iterate over player hand
  for (int i = 0; i < hand.getSize(); i++) {
    if (i < hand.getSize()-1) {
      // Add spacing
      std::cout << hand.getTileAt(i)->toString() << ", ";
    }
    else {
      std::cout << hand.getTileAt(i)->toString() << std::endl << std::endl;
    }
  }
}