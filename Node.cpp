#include "Node.h"

Node::Node(Tile* tile, Node* next) {
  this->tile = tile;
  this->next = next;
  this->prev = prev;
}

Node::Node(Node& other) {
  tile = other.tile;
  next = other.next;
  prev = other.prev;
}

std::string Node::toString() {
  return tile->toString();
}

Tile *Node::getTile() {
  return tile;
}
